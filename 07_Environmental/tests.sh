#! /bin/bash

echo "This is the text from the file to be hashed." > example.txt

md5sum example.txt > hashed_example.txt
sed -i 's/ .*//' hashed_example.txt

echo "TEST: md5 hash algorythm in rhasher and in md5sum"
echo "MD5 example.txt" | ./rhasher > rhasher_res.txt
sed -i -n '2p' rhasher_res.txt
diff rhasher_res.txt hashed_example.txt
if [ $? != "0" ]; then
    echo "MD5 example.txt" | ./rhasher > rhasher_res.txt
    sed -i -n '3p' rhasher_res.txt
    diff rhasher_res.txt hashed_example.txt
    if [ $? != "0" ]; then
        exit -1
    fi
fi

sha1sum example.txt > hashed_example.txt
sed -i 's/ .*//' hashed_example.txt

echo "TEST: sha1 hash algorythm in rhasher and in sha1sum"
echo "SHA1 example.txt" | ./rhasher > rhasher_res.txt
sed -i -n '2p' rhasher_res.txt
diff rhasher_res.txt hashed_example.txt
if [ $? != "0" ]; then
    echo "SHA1 example.txt" | ./rhasher > rhasher_res.txt
    sed -i -n '3p' rhasher_res.txt
    diff rhasher_res.txt hashed_example.txt
    if [ $? != "0" ]; then
        exit -1
    fi
fi
rm -rf hashed_example.txt rhasher_res.txt example.txt