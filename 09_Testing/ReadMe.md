Assembling and testing: autoreconf -fisv && ./configure --enable-gcov && make && make check

Coverage: make gcov

Clean: make gitclean