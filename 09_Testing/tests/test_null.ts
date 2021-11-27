#include "buf.h"

#test clearnull
	float *a = 0;
	buf_clear(a);
	ck_assert_int_eq(buf_size(a), 0);
	ck_assert(a == 0);
