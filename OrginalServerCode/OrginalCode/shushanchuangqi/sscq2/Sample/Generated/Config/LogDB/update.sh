#!/bin/bash

function update_object()
{
    echo "update [BEGIN]:"
    #mysql -h$1 -u$2 -p$3 -P$4 -D$5 <  updates/cjhupdate_2015_03_13_1.sql;
    #mysql -h$1 -u$2 -p$3 -P$4 -D$5 <  updates/update_2015_3_24_1.sql;
    #mysql -h$1 -u$2 -p$3 -P$4 -D$5 <  updates/update_2015_4_27_01.sql;
    mysql -h$1 -u$2 -p$3 -P$4 -D$5 <  updates/update_2015_4_29_01.sql;


    echo "update [DONE]"
}

update_object $1 $2 $3 $4 $5

