#include "buf.h"

#test initialization
	float *a = 0;
	ck_assert_int_eq(buf_capacity(a), 0);
	ck_assert_int_eq(buf_size(a), 0);
	buf_push(a, 1.3f);
	ck_assert_int_eq(buf_size(a), 1);
	ck_assert_float_eq(a[0], (float)1.3f);
	buf_clear(a);
	ck_assert_int_eq(buf_size(a), 0);
	ck_assert(a != 0);
	buf_free(a);
	ck_assert(a == 0);

