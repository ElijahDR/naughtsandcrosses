#!/bin/bash
g++ -Werror main2.cc -o main.o
if [[ $? == 0 ]]; then
    ./main.o
fi
