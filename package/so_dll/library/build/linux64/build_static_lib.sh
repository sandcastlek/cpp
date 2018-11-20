#!/bin/bash

#g++ -c ../../src/sort.cpp
#g++ -c ../../src/sort.cpp -o ../../out/lib/
g++ -c ../../src/sort.cpp -o ../../out/lib/sort.o
#ar rc ../../lib/sorting.a ../../out/lib/sort.o
ar rcs sorting.a ../../out/lib/sort.o

