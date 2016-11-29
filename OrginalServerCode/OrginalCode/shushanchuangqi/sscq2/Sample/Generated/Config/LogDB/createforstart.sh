#!/bin/bash
mysql -h$1 -u$2 -p$3 -P$4 -D$5 < TableForDate.sql;

