#include "ft_malcom.h"

int main(int argc, const char *argv[]){

	t_malcom *data = NULL;
//	const char str[] = "hey bud!\n";
	if (parse_args(argc, argv, data)) return 1;
	printf("Compiles\n");
	return 0;
}


