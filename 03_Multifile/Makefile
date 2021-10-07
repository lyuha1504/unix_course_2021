GENERAT = prog prog-a prog-so liboutput-static.a liboutput.so
OUTPUTS = *.output
TRASH = *.o *~ o.*
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)

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

%-0.output:	%
	LD_LIBRARY_PATH=`pwd` /bin/bash -c "(exec -a prog ./$^)" > $@ 2>&1

%-1.output:	%
	LD_LIBRARY_PATH=`pwd` /bin/bash -c "(exec -a prog ./$^ qwerty)" > $@ 2>&1

%-3.output:	%
	LD_LIBRARY_PATH=`pwd` /bin/bash -c "(exec -a prog ./$^ qw er ty)" > $@ 2>&1

test-%:	prog-%.output prog-a-%.output prog-so-%.output
	cmp prog-$*.output prog-a-$*.output
	cmp prog-$*.output prog-so-$*.output

test:	test-0 test-1 test-3

fun.o: outlib.h

prog.o: outlib.h

clean:
	rm -f $(SOURCES:.c=.o) $(TRASH) $(OUTPUTS)

distclean:	clean
	rm -rf $(GENERAT)