#!/bin/bash

LINE=$2
if [ -z $2 ]
then
	LINE="-wn"
elif [ "all" == "$2" ]
then
	LINE=""
else
	LINE="-wn"$2
fi
find . -iname \*.[ch] -exec grep $LINE -n --color -H $1 \{\} \;
find . -iname \*.cpp -exec grep $LINE -n --color -H $1 \{\} \;
find . -iname \*.lua -exec grep $LINE -n --color -H $1 \{\} \;


