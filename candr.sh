#!/bin/bash
g++ -Werror main.cc -o main.o
if [[ $? == 0 ]]; then
    ./main.o
fi;