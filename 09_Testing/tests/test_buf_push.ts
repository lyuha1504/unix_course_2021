#include "buf.h"

#test bufpush
	long *ai = 0;
	for (int i = 0; i < 10000; i++)
		buf_push(ai, i);
	ck_assert_int_eq(buf_size(ai), 10000);
	int match = 0;
	for (int i = 0; i < (int)(buf_size(ai)); i++)
		match += ai[i] == i;
	ck_assert_int_eq(match, 10000);
	buf_free(ai);
