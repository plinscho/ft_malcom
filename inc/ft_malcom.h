#ifndef FT_MALCOM_H
# define FT_MALCOM_H

/*
	man packet
*/

#include "libft/libft.h"

#include <stdio.h>// printf and related to printf
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//recvfrom and sendto
#include <errno.h>
#include <signal.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>// struct ethhdr, ETH_P_ARP, ETH_P_IP
#include <net/ethernet.h>// ETH_P_ALL definition
//#include <>

/* TYPEDEFS */
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr_ll t_sockaddr_ll;


/* STRUCTS */

typedef struct s_eth{
	t_sockaddr_in	host_sockaddr_in;// man sockaddr_in / Ipv4 socket address
	t_sockaddr_ll	host_sockaddr_ll;// man packet / physical layer address
	char		*hostname;
	char		*mac_addr;
}t_eth;

typedef struct s_malcom{
	t_eth		src_eth;
	t_eth		dst_eth;
}t_malcom;


// FUNCTIONS

// error.c
int error_print(const char *msg, int error_num);

// parser.c
int parse_args(int argc, const char *argv[], t_malcom *data);


#endif
