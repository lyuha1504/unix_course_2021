#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <rhash.h>
#include <unistd.h>
#include <ctype.h>
#include "config.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif


int main(int argc, char *argv[]) {

	char* input = NULL, * hash_name = NULL, * string_to_hash = NULL;
	char output[256];
	unsigned char digest[64];
	int hash_type = 0, output_type = 0;
	
	rhash_library_init();
	
	#ifdef USE_READLINE
	printf("Using readline!\n");
	while ((input = readline(NULL)) != NULL)
	#else
	size_t len = 0, is_read = 0;
	printf("Using getline!\n");
	while ((is_read = getline(&input, &len, stdin)) != -1)
	#endif
	{
	
		hash_name = strtok(input, " ");
		string_to_hash = strtok(strtok(NULL, " "), "\n");
		if (hash_name == NULL || string_to_hash == NULL) {
			fprintf(stderr, "Too few arguments, please execute in the following way:\n");
			fprintf(stderr, "<hash_name> <string_to_hash>\n");
			fprintf(stderr, "where <hash_name> in {MD5, SHA1, TTH}, <string_to_hash> is a string or file name\n");
			fprintf(stderr, "The string must start with \"\n");
			continue;
		}
		
		if (hash_name[0] == tolower(hash_name[0])) output_type = RHPR_BASE64;
		else output_type = RHPR_HEX;
		
		for (int i = 0; i < strlen(hash_name); ++i) hash_name[i] = tolower(hash_name[i]);
		
		if (strcmp(hash_name, "md5") == 0) hash_type = RHASH_MD5;
		else if (strcmp(hash_name, "sha1") == 0) hash_type = RHASH_SHA1;
		else if (strcmp(hash_name, "tth") == 0) hash_type = RHASH_TTH;
		else {
			fprintf(stderr, "Wrong hash type, it must be MD5, SHA1 or TTH\n");
			continue;
		}
		
		if (string_to_hash[0] == '\"') {
		
			string_to_hash++;
			int res = rhash_msg(hash_type, string_to_hash, strlen(string_to_hash), digest);
			if (res < 0) {
				fprintf(stderr, "Message digest calculation error\n");
				fprintf(stderr, "%s\n", strerror(errno));
				continue;
			}
		
		}
		else {
			
			int res = rhash_file(hash_type, string_to_hash, digest);
			if (res < 0) {
				fprintf(stderr, "Message digest calculation error\n");
				fprintf(stderr, "%s\n", strerror(errno));
				continue;
			}
			
		}
		
		rhash_print_bytes(output, digest, rhash_get_digest_size(hash_type), output_type);
		printf("%s\n", output);
		
		if (input != NULL) free(input);
		
	}

	return 0;

}