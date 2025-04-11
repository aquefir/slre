#!/bin/sh
#

cc -otest test.c slre.c
./test
rm -f test
