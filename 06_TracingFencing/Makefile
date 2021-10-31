move:	move.c
	cc -Wall -Wextra move.c -o move

my_remove.so:	my_remove.c
	cc -shared -fPIC -Wall -Wextra my_remove.c -o my_remove.so -ldl

infile_example.txt:
	echo "The text to be copied." > infile_example.txt

test:	move my_remove.so infile_example.txt test.sh
	./test.sh

clean:
	rm -rf move my_remove.so infile_example.txt input.txt input_PROTECT.txt output.txt