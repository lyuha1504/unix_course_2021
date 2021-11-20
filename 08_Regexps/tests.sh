#! /bin/bash

# not enough args
echo -e "Usage: ./esub regexp substitution string\nWorks like: echo 'string' | sed -E 's/regexp/substitution/'" > test.txt
./esub "" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# invalid regular expression
echo "Regcomp failed: Invalid regular expression" > test.txt
./esub "][" "\1" "abc" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# not closed sequence of brackets
echo "Regcomp failed: Unmatched ( or \(" > test.txt
./esub "()(" "\3" "abc" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# not enough pockets
echo "Not enough pockets in regular expression for pocket 3 value" > test.txt
./esub "()*" "\3" "abc" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# invalid regular expressionh
echo "Regcomp failed: Invalid preceding regular expression" > test.txt
./esub "(*" "\3" "abc" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# correct example no. 1
echo "abc" | sed -E "s/[[:alpha:]]/\0/" > test.txt
./esub "[[:alpha:]]" "\0" "abc" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# unclosed backslash sequence
echo -e "Unclosed sequence with \\ symbol in substitution string" > test.txt
./esub "(a.)*c" "\0\\" "abc" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# correct example no. 2
echo "a123b123c" | sed -E "s/(a.*)(b.*)c/\2 \1 \0/" > test.txt
./esub "(a.*)(b.*)c" "\2 \1 \0" "a123b123c" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# not enough pockets again
echo "Not enough pockets in regular expression for pocket 7 value" > test.txt
./esub "(a.*)(b.*)c" "\2 \7 \0" "a123b123c" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

# no match
echo "ABCSGDJHDE" | sed -E "s/(a.*)(b.*)c/\2 \0/" > test.txt
./esub "(a.*)(b.*)c" "\2 \0" "ABCSGDJHDE" &> esub_res.txt
diff esub_res.txt test.txt
if [ $? != "0" ]; then
    exit -1
fi

rm -rf test.txt esub_res.txt