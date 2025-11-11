#include "ft_malcom.h"

int	is_ip(const char *s){
	struct in_addr	tmp;
	return (inet_pton(AF_INET, s, &tmp) == 1);
}

int	is_hex_val(char c){
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
	if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
	return -1;
}

int	is_valid_mac(const char *s){
	size_t len = ft_strlen(s);
	if (len != 17) return 0;
	int flag = 2;
	for (size_t i = 0 ; i < len ; i++){
		if ((s[i] == ':'||s[i] == '-') && flag == 0){
			flag = 2;
			continue;
		} else if (is_hex_val(s[i]) && flag > 0){
			flag--;
			continue;
		} else {
			return 0;
		}
	}
	return 1;
}

void	macbin_to_str(char str[18], uint8_t mac[6]){  // Fix: 18, not 19
	if (!str || !mac) return;
	sprintf((char*)str, "%02x:%02x:%02x:%02x:%02x:%02x",
        mac[0], mac[1], mac[2],
        mac[3], mac[4], mac[5]);
}

// Check the address before stotage!
void	store_ip(t_sockaddr_in *addr, const char *new_ip){
	addr->sin_family = AF_INET;
	inet_pton(AF_INET, new_ip, &(addr->sin_addr));
}

int create_socket(t_malcom *data){
	if (!data)
		return error_msg("Error in create_socket()\nData not found.\n", 1);
	// This socket() function has to be run by a sudo user, or it will throw an error1
	data->socketfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP)); // man 7 raw
	if (data->socketfd < 0)
		return error_msg("Error creating raw socket\nDid you run ft_malcom with sudo?\n", 1);
	else
		printf("Socket created with fd: %d\n", data->socketfd);
	return 0;
}

