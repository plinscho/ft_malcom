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

// Check the address before stotage!
void	store_ip(t_sockaddr_in *addr, const char *new_ip){
	addr->sin_family = AF_INET;
	inet_pton(AF_INET, new_ip, &(addr->sin_addr));
}


