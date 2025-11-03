#include <ft_malcom.h>

int error_msg(const char *msg, int err){
	fprintf(stderr, "%s\n", msg);
	return err;
}

int error_usage(int ret_val){
	printf("Usage:\n");
	printf("./ft_malcom <ip sender> <MAC sender> <ip target> <MAC target>\n");
	return ret_val;
}

int error_print(int error_num){
	fprintf(stderr, "Error code: %d\n", error_num);
	fprintf(stderr, "Error msg: %s\n", strerror(error_num));
	return error_num;
}

