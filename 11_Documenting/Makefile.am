SUBDIRS = po

bin_PROGRAMS = guess

pkgdata_DATA = guess.1

@DX_RULES@

all-local:	doxygen-doc

%.1:	%
	$(HELP2MAN) --no-info --output=$@ --name='guesses the number from 1 to 100 by asking questions' ./$<
