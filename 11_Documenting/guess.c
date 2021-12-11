/** @file guess.c
	This program guesses the number from 1 to 100 by asking questions and using the dichotomy method.
	Additional -r option allows printing roman numbers instead of arabian. */

#include <stdlib.h>
#include <argp.h>
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"

#define _(string) gettext(string) /**< Macro for translation */

const char *argp_program_version = "guess 1.0";
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

/* Program documentation. */
static char doc[] = "Program for guessing a number from 1 to 100 (arabian or roman digits)";

/* The options we understand. */
static struct argp_option options[] = {
	{"print-help", 'p', 0, 0, "Print help in another language (locale)" },
	{"roman",      'r', 0, 0, "Work with roman digits instead of arabian" },
	{ 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments {
	int print_help; /**< Flag for printing help in another language (locale) */
	int roman;      /**< Roman numbers flag */
};

/**  
 * Parse a single option `key` with optional argument `arg` when state is `state`.
 *
 * @param key Commandline option
 * @param arg Optional key argument
 * @param state Internal parset state
 *
 *
 * @returns Error status
 * */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse, which we
	know is a pointer to our arguments structure. */
	struct arguments *arguments = state->input;

	switch (key) {
		case 'r':
			arguments->roman = 1;
			break;

		case 'p':
			arguments->print_help = 1;
			break;

		case ARGP_KEY_ARG:
		case ARGP_KEY_END:
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
static struct argp argp = { options, parse_opt, 0, doc };


const char* last_digit[10] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};       /**< last digit in roman */
const char* first_digit[11] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC", "C"}; /**< first digit in roman */

/**  
 * Transfer the arabian number to the roman one.
 * 
 * @param result String, which the result will be written in
 * @param number Number in arabian digits to be tranfered
 *
 *
 * @returns The result string that contains the roman look for the number
 * */
char* arab2roman (char* result, int number)
{		
	strcpy(result, first_digit[number / 10]);
	strcat(result, last_digit[number % 10]);
	return result; 
}


/**  
 * Transfer the roman number to the arabian one.
 * 
 * @param number Roman number
 *
 *
 * @returns Arabian number that equals the roman one
 * */
int roman2arab (char* number)
{		
	int result = 0;
	char* curr = number;
	int X = 0, L = 0, I = 0, V = 0;
	while (curr) {
		switch (*curr) {
			case 'I':
				if (X || L) {
					result += L * 50 + X * 10;
					X = 0; L = 0;
				}
				I++;
				break;
			case 'V':
				if (I) {
					result += 4;
					I = 0; V = 0;
				}
				else if (X || L) {
					result += L * 50 + X * 10;
					X = 0; L = 0;
				}
				else V++;
				break;
			case 'X':
				if (I) {
					result += 9;
					I = 0; X = 0;
				}
				X++;
				break;
			case 'L':
				if (X) {
					result += 40;
					X = 0; L = 0;
				}
				else L++;
				break;
			case 'C':
				if (X) result += 90;
				else result += 100;
				X = 0;
				break;
		}
		curr++;
	}
	result += L * 50 + X * 10 + V * 5 + I;
	return result; 
}


int main (int argc, char **argv)
{
	setlocale(LC_ALL, "");
	bindtextdomain("guess", "po");
	textdomain("guess");

	struct arguments arguments;

	/* Default values. */
	arguments.print_help = 0;
	arguments.roman = 0;

	/* Parse our arguments; every option seen by parse_opt will
	be reflected in arguments. */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	
	if (arguments.print_help) {
		printf(_("Usage: guess [OPTION...] \n"));
		printf(_("Program for guessing a number from 1 to 100 (arabian or roman digits) \n"));
		printf("\n");
		printf(_("  -p, --print-help           Print help in another language (locale)"));
		printf("\n");
		printf(_("  -r, --roman                Work with roman numbers instead of arabian"));
		printf("\n");
		printf(_("  -?, --help                 Give this help list \n"));
		printf(_("      --usage                Give a short usage message \n"));
		printf(_("  -V, --version              Print program version \n"));
		printf("\n");
		printf(_("Report bugs to lyuha1504@yandex.ru. \n"));
		printf("\n");
		exit(0);
	}
	
	int ibeg = 1, iend = 100;
	int icurr, res;
	
	const char *yes_string = _("yes");
	const char *no_string = _("no");
	char answer[10], roman_number[10];
	
	printf(_("Pick any number from 1 to 100 and press ENTER "));
	printf(arguments.roman ? _("(roman digits)\n") : _("(arabian digits)\n"));
	getchar();
	
	do {
		icurr = (ibeg + iend) / 2;
		printf(_("Is your number larger than "));
		if (arguments.roman) {
			arab2roman(roman_number, icurr);
			printf("%s ", roman_number);
		}
		else printf("%d ", icurr);
		printf(_(" (yes/no)? : "));
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
	
	printf(_("Your number is "));
	if (arguments.roman) {
		arab2roman(roman_number, ibeg);
		printf("%s\n", roman_number);
	}
	else printf("%d\n", ibeg);

	exit (0);
}
