#include "ex3.h"


int main(){
	StringVector *result = create_string_vector(1);
	char s[1000];
	fgets(s, 1000,stdin);
	error_msg error = FilesStrStr(2, result, s, "ex3/test1", "ex3/test2");
	if (error) {
		destroy_string_vector(result);
		return print_error(error);
	}
	print_string_vector(stdout, result, "");
	destroy_string_vector(result);

	return NORMAL;
}