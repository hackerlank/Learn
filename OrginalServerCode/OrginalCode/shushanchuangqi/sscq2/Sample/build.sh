#!/bin/sh

config=$1
if [ -z $config ]
then
    config=debug
else
	config=release
fi

if [ $config != "debug" ] && [ $config != "release" ] && [ $config != "tarball" ]
then
	echo Must Specify debug or release or tarball!
	exit 1
fi

make -j8 $config
