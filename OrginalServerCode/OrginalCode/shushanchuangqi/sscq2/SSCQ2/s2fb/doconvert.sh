#!/bin/bash
f1=../$1
f2=`echo $f1|sed s/$/.tmp/`
echo "Converting "$f1
cd convert && java JFConvert $f1 $f2 1
mv -f $f2 $f1
