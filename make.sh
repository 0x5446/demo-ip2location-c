#!/bin/sh

gcc src/test.c -lm -O3 -o bin/test
gcc src/ip2location.c -lm -O3 -o bin/ip2location
