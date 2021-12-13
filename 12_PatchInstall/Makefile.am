AM_CPPFLAGS = -D LOCALEDIR='"$(localedir)"'

bin_PROGRAMS = guess

man1_MANS = guess.1

pkgdata_DATA = ru/LC_MESSAGES/guess.mo
pkgdatadir = $(localedir)/ru/LC_MESSAGES

%.1:	%
	$(HELP2MAN) --no-info --output=$@ --name='guesses the number from 1 to 100 by asking questions' ./$<

ru/LC_MESSAGES/guess.mo:	ru.po
	mkdir -p `dirname $@`
	msgfmt -o $@ $<

ru.po:	messages.pot
	msgmerge -U $@ $<

messages.pot:	guess.c guess.pot
	xgettext -k_ -L C -c $< -o messages.new.pot
	cp guess.pot $@
	msgmerge -U $@ messages.new.pot

gitclean:
	git clean -fd