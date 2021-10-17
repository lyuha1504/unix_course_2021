#!/bin/bash

sleep_time=0.05
if [ $# -ge 1 ]; then sleep_time=$1; fi

hex_file=$(od -v -An -t x1 -w1 - | tr -d ' ' | tr '\n' ' ')

x=0
y=0
pos=''
for ch in $hex_file; do 
    if [ "$ch" = "20" ]; then 
        x=$(($x + 1)) 
    elif [ "$ch" = "0a" ]; then 
        y=$(($y+1)) 
	x=0
    else 
        s="$y $x $ch"
	if [ -z "$pos" ]; then
	    pos=$s
	else
	    pos="$pos\n$s"
	fi
	x=$(($x + 1)) 
    fi
done

shuffled=$(echo -e "$pos" | shuf)

tput clear
echo "$shuffled" |
while read x y ch; do
	sleep $sleep_time
	tput cup $x $y
	echo -ne "\x$ch"
done

tput cup $(tput lines) 0