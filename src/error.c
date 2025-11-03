#include <ft_malcom.h>

int error_print(const char *msg, int error_num){
	if (msg){
		fprintf(stderr, "msg: %s\n", msg);
	}
	fprintf(stderr, "Error code: %d\n", error_num);
	fprintf(stderr, "Error msg: %s\n", strerror(error_num));
	return error_num;
}

