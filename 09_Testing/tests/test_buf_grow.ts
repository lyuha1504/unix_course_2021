#include "buf.h"

#test bufgrow
	long *ai = 0;
	buf_grow(ai, 1000);
	ck_assert_int_eq(buf_capacity(ai), 1000);
	ck_assert_int_eq(buf_size(ai), 0);
	buf_trunc(ai, 100);
	ck_assert_int_eq(buf_capacity(ai), 100);
	buf_free(ai);
