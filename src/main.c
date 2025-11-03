#include "ft_malcom.h"

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

int main(int argc, const char *argv[]){
	t_malcom *data = get_new_malcom();
	if (!data)
		return (error_msg("Malloc error!", 1));
	if (parse_args(argc, argv, data)){
		free_malcom(data);
		return 1;
	}
	// ip4 and ip6 now stored in data as strings
	if (create_socket(data)){
		free_malcom(data);
		return 1;
	}
	printf("Success!\nExiting now.\n");
	free_malcom(data);
	return 0;
}


