pkgdata_DATA = ru/LC_MESSAGES/guess.mo

ru/LC_MESSAGES/guess.mo:	ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt $< -o $@

ru.po:	messages.pot
	msgmerge -U $@ $<

messages.pot:	../guess.c guess.pot
	xgettext -k_ -c -L C -o messages.new.pot $<
	cp guess.pot $@
	msgmerge -U $@ messages.new.pot