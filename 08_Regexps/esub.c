#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "config.h"

#define PM 10


void error_exit(int res, regex_t *r, const char *message) {

	int message_size = regerror(res, r, NULL, 0);
	char *error_message = (char*) malloc(message_size * sizeof(char));
	
	regerror(res, r, error_message, message_size);
	fprintf(stderr, "%s: %s\n", message, error_message);

	free(error_message);
	regfree(r);
	exit(1);

}


void make_the_substitution(char* substitution, char* string, regmatch_t* pm) {

	int length = strlen(substitution);
	char* processed_subst = (char*) malloc(length * sizeof(char));
	int i, index = 0, was_slash = 0;
	char *p, *p_proc;

	//preprocess the substitution string to substitute '\\' with '\'
	p_proc = processed_subst;
	for (p = substitution; *p; p++) {
		if (*p == '\\') {
			if (!was_slash) {
				*p_proc = *p;
				p_proc++;
			}
			was_slash = 1 - was_slash;
		}
		else {
			*p_proc = *p;
			p_proc++;
			was_slash = 0;
		}
	}
	*p_proc = '\0';

	if (was_slash) {
		fprintf(stderr, "Unclosed sequence with \\ symbol in substitution string\n");
		exit(1);
	}

	//check if all of the pockets exist
	was_slash = 0;
	for (p = processed_subst; *p; p++) {
		if (*p == '\\') was_slash = 1 - was_slash;
		else if (isdigit(*p) && was_slash) {
			int pocket_num = *p - '0';
			int start_point = (int) pm[pocket_num].rm_so;
			if (start_point < 0) {
				fprintf(stderr, "Not enough pockets in regular expression for pocket %d value\n", pocket_num);
				free(processed_subst);
				exit(1);
			}
			was_slash = 0;
		}
		else was_slash = 0;
	}

	//print the string with substitutions
	int start = (int) pm[0].rm_so;
	for (i = 0; i < start; ++i) putchar(string[i]);
	was_slash = 0;
	for (p = processed_subst; *p; p++) {
		if (*p == '\\') {
			if (was_slash) putchar(*p);
			was_slash = 1 - was_slash;
		}
		else if (isdigit(*p)) {
			int pocket_num = *p - '0';
			int start_point = (int) pm[pocket_num].rm_so;
			int end_point = (int) pm[pocket_num].rm_eo;
			for (i = start_point; i < end_point; ++i) putchar(string[i]);
			was_slash = 0;
		}
		else {
			putchar(*p);
			was_slash = 0;
		}
	}
	printf("%s\n", string + pm[0].rm_eo);

	free(processed_subst);

}


int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("Usage: %s regexp substitution string\n", argv[0]);
		printf("Works like: echo \'string\' | sed -E \'s/regexp/substitution/\'\n");
		return 1;
	}

	char *regexp = argv[1], *substitution = argv[2], *string = argv[3];
	regex_t r;
	regmatch_t pm[PM];
	int res;

	res = regcomp(&r, regexp, REG_EXTENDED);
	if (res != 0) error_exit(res, &r, "Regcomp failed");

	res = regexec(&r, string, PM, pm, 0);
	if (res == 0) {
		make_the_substitution(substitution, string, pm);
		regfree(&r);
	}
	else if (res == REG_NOMATCH) {
		printf("%s\n", string);
		regfree(&r);
	}
	else error_exit(res, &r, "Regexec failed");

	return 0;

}
