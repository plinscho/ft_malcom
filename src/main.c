#include "ft_malcom.h"

int main(int argc, const char *argv[]){
	t_malcom *data = NULL;
	if (parse_args(argc, argv, data)) return 1;

	printf("Success!\nExiting now.\n");
	return 0;
}


