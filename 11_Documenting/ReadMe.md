Assembling:	autoreconf -fisv && ./configure && make

Launching the prog:	./guess [-pr?V] [--print-help] [--roman] [--help] [--usage] [--version]

Launch server:	python3 -m http.server --directory doxygen-doc/html

See documentation:	go to localhost:8000

See manual:	man -l guess.1

Clean the generates:	git clean -fd