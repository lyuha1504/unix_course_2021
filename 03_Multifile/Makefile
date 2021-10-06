GENERAT = prog prog-a prog-so
READMES = README README-A README-SO
OUTPUTS = output-1 output-2 output-a-1 output-a-2 output-so-1 output-so-2
TRASH = *~ o.*
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)
LIBS = liboutput-static.a liboutput.so

all:	prog prog-a prog-so

prog:	const.o fun.o prog.o

prog-a:	prog.o liboutput-static.a
	cc -L. $< -loutput-static -o $@

prog-so:	prog.o liboutput.so
	cc -L. $< -loutput -o $@

liboutput-static.a:	fun.o const.o
	ar -rcs $@ $^

liboutput.so:	fun.o const.o
	cc -shared $^ -o $@

test:	prog prog-a prog-so
	./prog 2> README
	./prog-a 2> README-A
	LD_LIBRARY_PATH=`pwd` ./prog-so 2> README-SO
	./prog qwerty > output-1
	./prog-a qwerty > output-a-1
	LD_LIBRARY_PATH=`pwd` ./prog-so qwerty > output-so-1
	cmp -b output-1 output-a-1
	cmp -b output-a-1 output-so-1
	cmp -b output-1 output-so-1
	./prog qw er ty > output-2
	./prog-a qw er ty > output-a-2
	LD_LIBRARY_PATH=`pwd` ./prog-so qw er ty > output-so-2
	cmp -b output-2 output-a-2
	cmp -b output-a-2 output-so-2
	cmp -b output-2 output-so-2

clean:
	rm -f $(SOURCES:.c=.o) $(TRASH) $(READMES) $(OUTPUTS)

distclean:	clean
	rm -rf $(GENERAT) $(LIBS)