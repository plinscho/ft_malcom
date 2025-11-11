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
	uint16_t idx = if_nametoindex("enp4s0");
	printf("enp4s0 index: %d\n\n", idx); 

	// We have the socket, now we have to receive the ARP request

	unsigned char	buffer[BUF_SIZE];
	socklen_t		sock_len = sizeof(data->src_eth.host_sockaddr_ll);
	t_sockaddr_ll	*buff_eth = &data->src_eth.host_sockaddr_ll;
	t_ethhdr 		*eth_res = NULL;
	t_arp			*arp_res = NULL;
	while (isOn){
		sigaction(SIGINT, &act, NULL);
		sock_len = sizeof(*buff_eth);

		// Receive the raw bytes of the ethernet frame
		// recvfrom(int socket, struct sockaddr* src, socklen_t)
		ssize_t bytes = recvfrom(data->socketfd, buffer, BUF_SIZE, 0, (struct sockaddr*)buff_eth, &sock_len);

		if (bytes < 0 && isOn) {
			fprintf(stderr, "Error.\nrecvfrom() failed!\n");
			continue;
		} else if (bytes < (ssize_t)sizeof(t_ethhdr) + 28){
			continue;
		}
		eth_res = (t_ethhdr*)buffer;
		if (ntohs(eth_res->h_proto) != ETH_P_ARP)
			continue;
		
		arp_res = (t_arp*)(buffer + ETH2_HEADER_LEN); // start of packet + 14 bytes (Skip headers)
		if (ntohs(arp_res->opcode) != 1) 
			continue;
		// Found ARP request!
		uint32_t target_ip = data->src_eth.host_sockaddr_in.sin_addr.s_addr;
		if (target_ip == *(arp_res->tpa)){
			printf("FOUND REQUEST BY TARGET IP\n");
			break;
		}
		sleep(0.2);
	}
	printf("Exiting now.\n");
	free_malcom(data);
	return 0;
}
