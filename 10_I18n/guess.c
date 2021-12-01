#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext(string)

int main(void) {

	int ibeg = 1, iend = 100;
	int icurr, res;

	setlocale(LC_ALL, "");
	bindtextdomain("guess", "po");
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