#include "ft_malcom.h"

int parse_args(int argc, const char *argv[], t_malcom *data){
	if (argc != 4 || !argv || !argv [0]){
		return 1;
	}
	ft_bzero((void*)data, 0);
	return 0;
}	

