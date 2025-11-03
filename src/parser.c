#include "ft_malcom.h"

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
	return 0;
}	

