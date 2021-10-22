range:	range.c
	cc -g -O0 $^ -o $@

test%.txt:	test%.gdb range
	gdb --quiet --batch-silent --command=$< ./range 
	cat gdb.txt | grep @@@ | cut -c 5- > $@
	rm -f gdb.txt

test1:	test1.txt test1.ex
	diff $^

test2:	test2.txt test2.ex
	diff $^

test:	test1 test2

clean:
	rm -f range test1.txt test2.txt