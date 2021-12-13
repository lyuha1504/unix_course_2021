#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <argp.h>
#include "config.h"

#define _(string) gettext(string)

const char *argp_program_version = "guess 0.0";
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

/* Program documentation. */
static char doc[] = "Program for guessing a number from 1 to 100";

/* Arguments parser */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse, which we
	know is a pointer to our arguments structure. */
	struct arguments *arguments = state->input;

	switch (key) {
		case ARGP_KEY_ARG:
			if (state->arg_num >= 1)
			/* Too many arguments. */
				argp_usage (state);
			break;

		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/* Our argp parser. */
static struct argp argp = { 0, parse_opt, 0, doc };


/* Main function. */
int main(int argc, char *argv[]) {

	argp_parse(&argp, argc, argv, 0, 0, 0);

	int ibeg = 1, iend = 100;
	int icurr, res;

	setlocale(LC_ALL, "");
	bindtextdomain("guess", LOCALEDIR);
	textdomain("guess");
	
	const char *yes_string = _("yes");
	const char *no_string = _("no");
	char answer[10];
	
	puts(_("Pick any number from 1 to 100 and press ENTER"));
	getchar();
	
	do {
		icurr = (ibeg + iend) / 2;
		printf(_("Is your number larger than %d (yes/no)? : "), icurr);
		res = scanf("%s", answer);
		if (res == EOF) {
			printf(_("The input is incorrect, try again\n"));
			continue;
		}
		if (strcmp(answer, yes_string) == 0) ibeg = icurr + 1;
		else if (strcmp(answer, no_string) == 0) iend = icurr;
		else {
			printf(_("The answer is in the wrong form, try again\n"));
			continue;
		}
	} while (ibeg < iend);
	
	printf(_("Your number is %d\n"), ibeg);
	
	return 0;

}