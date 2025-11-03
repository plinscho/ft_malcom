#include <ft_malcom.h>

// Prints a message and returns the ret value
int error_msg(const char *msg, int ret){
	fprintf(stderr, "%s\n", msg);
	return ret;
}

int error_usage(int ret_val){
	printf("Usage:\n");
	printf("sudo ./ft_malcom <ip sender> <MAC sender> <ip target> <MAC target>\n");
	return ret_val;
}

// Prints the error number using strerror function
int error_print(int error_num){
	fprintf(stderr, "Error code: %d\n", error_num);
	fprintf(stderr, "Error msg: %s\n", strerror(error_num));
	return error_num;
}

