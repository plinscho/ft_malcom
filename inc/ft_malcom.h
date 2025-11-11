#ifndef FT_MALCOM_H
# define FT_MALCOM_H

/*
	man packet
*/

#include "libft/libft.h"

#include <stdio.h>// printf and related to printf
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>//recvfrom and sendto
#include <errno.h>
#include <signal.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <net/if.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>// struct ethhdr, ETH_P_ARP, ETH_P_IP
#include <net/ethernet.h>// ETH_P_ALL definition


#define PACKET_SIZE 60
#define BUF_SIZE 1500
#define ETH2_HEADER_LEN 14

/* TYPEDEFS */
typedef struct ethhdr		t_ethhdr;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr_ll	t_sockaddr_ll;


/* STRUCTS */

/*

The sockaddr_ll structure is a device-independent physical-layer address.
(Ethernet Frames inspector)

    struct sockaddr_ll {
        unsigned short sll_family;    Always AF_PACKET
        unsigned short sll_protocol;  Physical-layer protocol 
        int            sll_ifindex;   Interface number 
        unsigned short sll_hatype;    ARP hardware type 
        unsigned char  sll_pkttype;   Packet type 
        unsigned char  sll_halen;     Length of address 
        unsigned char  sll_addr[8];   Physical-layer address 
    };

Keep in mind that an ethernet frame is not the same as the struct 
sockaddr_ll (See README.md). A internet header in linux is 16 bytes
and contains a src & dst MAC address + EtherType / Protocol (6 + 6 + 2)bytes = 14 bytes (ETH2_HEADER_LEN)

*/


// ARP payload
// https://en.wikipedia.org/wiki/Address_Resolution_Protocol
typedef struct s_arp{
	uint16_t	htype; 		// Hardware type 16 bits (1 for ethernet)
	uint16_t	ptype; 		// Protocol type 16 bits (0x0800) for Ipv4
	uint8_t		hlen;  		// Hardware len  8  bits
	uint8_t		plen;  		// Protocol len  8  bits
	uint16_t	opcode;		// Operat code   16 bits (1 for ARP request)
	uint8_t		sha[6];		// sender addres 8*6 bits = 48
	uint8_t		tha[6];		// target addres 8*6 bits = 48 (ignored for request)
	uint8_t		spa[4];		// sender protocol address (internetwork address)
	uint8_t		tpa[4];		// target protocol address
} __attribute__((packed)) t_arp;

typedef struct s_eth{
	t_sockaddr_in	host_sockaddr_in;// man sockaddr_in / Ipv4 socket address
	t_sockaddr_ll	host_sockaddr_ll;// man packet / physical layer address
	t_ethhdr		eth_header;
	char			*hostname;
	char			*mac_addr;
}t_eth;

typedef struct s_malcom{
	t_eth			src_eth;
	t_eth			dst_eth;
	int				socketfd;
}t_malcom;


// FUNCTIONS

// error.c
int 	error_msg(const char *msg, int err);
int 	error_print(int error_num);
int 	error_usage(int ret_val);


// parser.c
int		parse_args(int argc, const char *argv[], t_malcom *data);
void	print_eth_header(t_sockaddr_ll *eth_frame);

// ip.c
int		is_ip(const char *s);
int		is_valid_mac(const char *s);
void	store_ip(t_sockaddr_in *addr, const char *ip);
int 	create_socket(t_malcom *data);
//void	print_arp_packet(t_arp *arp);  // Add this for debugging

// memory.c
void    free_malcom(t_malcom *m);

#endif
