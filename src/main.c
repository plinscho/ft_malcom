#include "ft_malcom.h"
#include <signal.h>
#include <stdbool.h>

static bool isOn = true;

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

*/

int main(int argc, const char *argv[]){
	struct sigaction act;
	t_malcom *data = get_new_malcom();
	
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
	if (!data)
		return (error_msg("Malloc error!", 1));
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

	// We have the socket, now we have to receive the ARP request
	//t_arp		arp_pkt;
	uint8_t		buffer[PACKET_SIZE];
	socklen_t	sock_len = 0;
	while (isOn){
		// recvfrom(int socket, struct sockaddr* src, socklen_t)
		ssize_t bytes = recvfrom(data->socketfd, 
									buffer, 
									PACKET_SIZE, 
									0, 
									(struct sockaddr*)&data->src_eth,
									&sock_len);

		sigaction(SIGINT, &act, NULL);
		if (bytes < 0 && isOn) {
			fprintf(stderr, "Error.\nrecvfrom() failed!\n");
			break;
		}
		(void)buffer;
	}
	printf("Exiting now.\n");
	free_malcom(data);
	return 0;
}


