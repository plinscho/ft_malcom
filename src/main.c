#include "ft_malcom.h"
#include <signal.h>
#include <stdbool.h>

static volatile bool isOn = true;

void	signal_handler(int signum){
	(void)signum;
	const char msg[] = "\nCtrl-C received!\nClosing server...\n";
	write(STDOUT_FILENO, msg, sizeof(msg) - 1);
	isOn = false;
}

t_malcom *get_new_malcom(){
	t_malcom *new = (t_malcom*)malloc(sizeof(t_malcom));
	if (!new) {
		fprintf(stderr, "Error!\nMalloc failed.\n");
		return NULL;
	}
	ft_bzero(new, sizeof *new);
	new->socketfd = -1;
	return new;
}

/*
SUBJECT:
When started, your program will have to wait for an ARP request sent on the broadcast
by the target, requesting the source IP, before sending a single ARP reply to the
target and exit. If everything went well, the arp table on the target should contain the
associated ip and mac you provided as source.

Remeber that the source IP does not have to be the same as your machine IPv4,
you can PRETEND to be another IP like default gateway.

*/

int main(int argc, const char *argv[]){
	struct sigaction act;
	t_malcom *data = get_new_malcom();
	if (!data)
		return (error_msg("Malloc error!", 1));
	
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = signal_handler;
	if (sigaction(SIGINT, &act, NULL) == -1){
		free_malcom(data);
		return 1;
	}
	if (getuid() != 0){
		free_malcom(data);
		return error_msg("Error in getuid().\nRun with 'sudo ./ft_malcom'\n", 1);
	}
	if (parse_args(argc, argv, data)){
		free_malcom(data);
		return 1;
	}

	// ip4 and ip6 now stored in data as strings
	// create a socket to capture the request paquet
	if (create_socket(data)){
		free_malcom(data);
		return 1;
	}
	
	// Get default interface or use provided one
	const char *interface = "eth0";  // Default, but you should detect this
	uint16_t idx = if_nametoindex(interface);
	if (idx == 0) {
		interface = "enp4s0";  // Fallback
		idx = if_nametoindex(interface);
	}
	if (idx == 0) {
		interface = "veth0";  // For testing
		idx = if_nametoindex(interface);
	}
	printf("Using interface %s (index: %d)\n\n", interface, idx);

	// We have the socket, now we have to receive the ARP request

	unsigned char	buffer[BUF_SIZE];
	struct sockaddr_ll	packet_info;  // This will contain metadata about the received packet
	socklen_t		sock_len;
	t_ethhdr 		*eth_header = NULL;
	t_arp			*arp_packet = NULL;
	
	printf("Waiting for ARP request for IP: %s\n", data->src_eth.hostname);
	
	while (isOn){
		sigaction(SIGINT, &act, NULL);
		sock_len = sizeof(packet_info);

		// Receive the raw bytes of the ethernet frame
		// buffer: contains the actual packet data (Ethernet header + ARP packet)
		// packet_info: contains metadata about where the packet came from
		ssize_t bytes = recvfrom(data->socketfd, buffer, BUF_SIZE, 0, 
								(struct sockaddr*)&packet_info, &sock_len);

		if (bytes < 0 && isOn) {
			fprintf(stderr, "Error.\nrecvfrom() failed!\n");
			continue;
		} else if (bytes < (ssize_t)sizeof(t_ethhdr) + sizeof(t_arp)){
			continue;  // Packet too small to contain Ethernet + ARP
		}
		
		// Parse the Ethernet header from the raw packet data
		eth_header = (t_ethhdr*)buffer;
		if (ntohs(eth_header->h_proto) != ETH_P_ARP)
			continue;
		
		// Parse the ARP packet (starts after Ethernet header)
		arp_packet = (t_arp*)(buffer + ETH2_HEADER_LEN);
		if (ntohs(arp_packet->opcode) != 1)  // Only ARP requests (opcode 1)
			continue;
		
		// Check if this ARP request is asking for the IP we want to spoof
		uint32_t spoofed_ip;
		inet_pton(AF_INET, data->src_eth.hostname, &spoofed_ip);
		
		if (ft_memcmp(&spoofed_ip, arp_packet->tpa, 4) == 0){
			printf("FOUND ARP REQUEST FOR TARGET IP: %s\n", data->src_eth.hostname);
			printf("Request came from: %d.%d.%d.%d\n", 
				   arp_packet->spa[0], arp_packet->spa[1], 
				   arp_packet->spa[2], arp_packet->spa[3]);
			printf("Requesting MAC for: %d.%d.%d.%d\n",
				   arp_packet->tpa[0], arp_packet->tpa[1],
				   arp_packet->tpa[2], arp_packet->tpa[3]);
			break;
		}
	}
	printf("Exiting now.\n");
	free_malcom(data);
	return 0;
}
