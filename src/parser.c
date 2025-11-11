#include "ft_malcom.h"

void	print_eth_header(t_sockaddr_ll *eth_frame){
	if (!eth_frame){ return ;}
	printf("sll_family\t\t: %d\n", eth_frame->sll_family);
	printf("sll_protocol\t\t: %d\n", eth_frame->sll_protocol);
	printf("sll_ifindex\t\t: %d\n", eth_frame->sll_ifindex);
	printf("sll_hatype\t\t: %d\n", eth_frame->sll_hatype);
	printf("sll_pkttype\t\t: %d\n", eth_frame->sll_pkttype);
	printf("sll_halen\t\t: %d\n", eth_frame->sll_halen);
	printf("sll_addr\t\t: %02x:%02x:%02x:%02x:%02x:%02x\n\n",
        (unsigned char)eth_frame->sll_addr[0],
        (unsigned char)eth_frame->sll_addr[1],
        (unsigned char)eth_frame->sll_addr[2],
        (unsigned char)eth_frame->sll_addr[3],
        (unsigned char)eth_frame->sll_addr[4],
        (unsigned char)eth_frame->sll_addr[5]);
}

void print_arp_packet(t_arp *arp) {
    if (!arp) return;
    
    printf("=== ARP Packet ===\n");
    printf("Hardware Type: %d\n", ntohs(arp->htype));
    printf("Protocol Type: 0x%04x\n", ntohs(arp->ptype));
    printf("Hardware Length: %d\n", arp->hlen);
    printf("Protocol Length: %d\n", arp->plen);
    printf("Opcode: %d\n", ntohs(arp->opcode));
    
    printf("Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           arp->sha[0], arp->sha[1], arp->sha[2],
           arp->sha[3], arp->sha[4], arp->sha[5]);
    
    printf("Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           arp->tha[0], arp->tha[1], arp->tha[2],
           arp->tha[3], arp->tha[4], arp->tha[5]);
    
    printf("Sender IP: %d.%d.%d.%d\n",
           arp->spa[0], arp->spa[1], arp->spa[2], arp->spa[3]);
    
    printf("Target IP: %d.%d.%d.%d\n",
           arp->tpa[0], arp->tpa[1], arp->tpa[2], arp->tpa[3]);
    printf("==================\n\n");
}

void print_cmp_arp(t_arp* arp_packet, const char *target){

	printf("Comparing: requested IP vs our target IP\n");
	printf("Requested: %d.%d.%d.%d\n", 
		   arp_packet->tpa[0], arp_packet->tpa[1],
		   arp_packet->tpa[2], arp_packet->tpa[3]);
	printf("Our target: %s\n", target);

}

int check_argv(const char *argv[]){
	if (!(is_ip(argv[1])) || !(is_ip(argv[3])))
		return error_msg("Ipv4 not valid\n", 1);
	if (!is_valid_mac(argv[2]) || !is_valid_mac(argv[4]))
		return error_msg("Ipv6 not valid.\n", 1);
	return 0;
}

int parse_args(int argc, const char *argv[], t_malcom *data){
	if (argc != 5 || check_argv(argv)){
		return (error_usage(1));
	}
	
	// copy IPv4 and IPv6 tot the data struct
	data->src_eth.hostname = ft_strdup((char*)argv[1]);
	data->src_eth.mac_addr = ft_strdup((char*)argv[2]);
	data->dst_eth.hostname = ft_strdup((char*)argv[3]);
	data->dst_eth.mac_addr = ft_strdup((char*)argv[4]);
	
	// check for malloc error in copies
	if (!data->src_eth.hostname ||
		!data->src_eth.mac_addr ||
		!data->dst_eth.hostname ||
		!data->dst_eth.mac_addr
	) return 1;
	else return 0;
}

