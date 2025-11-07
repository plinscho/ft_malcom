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

