#!/bin/sh


cp infile_example.txt input.txt
echo "TEST: cannot open the input file (operation not permitted)"
strace -eopenat -e fault=openat:error=EPERM:when=3 ./move input.txt output.txt
if [ $? -ne 3 ] || [ ! -f input.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi


cp infile_example.txt input.txt
echo ""
echo "TEST: cannot open the input file (no pemission at all)"
strace -eopenat -e fault=openat:error=EACCES:when=3 ./move input.txt output.txt
if [ $? -ne 3 ] || [ ! -f input.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi


cp infile_example.txt input.txt
echo ""
echo "TEST: cannot open the input file (no file)"
strace -eopenat -e fault=openat:error=ENOENT:when=3 ./move input.txt output.txt
if [ $? -ne 3 ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi
    
    
cp infile_example.txt input.txt
echo ""
echo "TEST: cannot open the output file (no permission at all)"
strace -eopenat -e fault=openat:error=EACCES:when=4 ./move input.txt output.txt
if [ $? -ne 4 ] || [ ! -f input.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi
    

cp infile_example.txt input.txt
echo ""
echo "TEST: cannot open the output file (operation not permitted)"
strace -eopenat -e fault=openat:error=EPERM:when=4 ./move input.txt output.txt
if [ $? -ne 4 ] || [ ! -f input.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi
  
    
cp infile_example.txt input.txt
echo ""
echo "TEST: cannot read from the input file (bad descriptor)"
strace -eread -e fault=read:error=EBADF:when=2 ./move input.txt output.txt
if [ $? -ne 5 ] || [ ! -f input.txt ] || [ -f output.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi
  
cp infile_example.txt input.txt
echo ""
echo "TEST: cannot write into the output file (no permission)"
strace -ewrite -e fault=write:error=EPERM:when=1 ./move input.txt output.txt
if [ $? -ne 8 ] || [ ! -f input.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi
  
    
cp infile_example.txt input.txt
echo ""
echo "TEST: cannot close the output file (no permission)"
strace -eclose -e fault=close:error=EACCES:when=3 ./move input.txt output.txt
if [ $? -ne 8 ] || [ ! -f input.txt ] || [ ! -f output.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi


cp infile_example.txt input.txt
echo ""
echo "TEST: cannot close the input file (no permission)"
strace -eclose -e fault=close:error=EACCES:when=4 ./move input.txt output.txt
if [ $? -ne 7 ] || [ ! -f input.txt ] || [ -f output.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi

cp infile_example.txt input.txt
echo ""
echo "TEST: cannot delete the input file (no permission)"
strace -eunlink -e fault=unlink:error=EACCES:when=1 ./move input.txt output.txt
if [ $? -ne 10 ] || [ ! -f input.txt ] || [ ! -f output.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi
  
    
cp infile_example.txt input_PROTECT.txt
echo ""
echo "TEST: do not delete the file with PROTECT in its name"
LD_PRELOAD=./my_remove.so ./move input_PROTECT.txt output.txt
if [ $? -ne 0 ] || [ ! -f input_PROTECT.txt ] || [ ! -f output.txt ]; then 
    echo "Test failed." 
    exit $?
else
    echo "Test successfully passed."
fi


echo ""
echo "All tests successfully passed."