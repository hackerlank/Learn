#!/bin/bash

source prepare.sh

cd $PROT && svn up && pwd && chmod +x genall.sh && ./genall.sh && cd -
if [ $? -ne 0 ]; then
    echo  "ERROR: Proto gen."
    return
fi

