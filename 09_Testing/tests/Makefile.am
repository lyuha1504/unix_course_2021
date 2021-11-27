TESTS = test_init test_null test_buf_push test_buf_grow test_buf_pop
check_PROGRAMS = test_init test_null test_buf_push test_buf_grow test_buf_pop

CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
