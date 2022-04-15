#!/bin/sh

clea;
make clean;
make fmt; 
make test;
./build/test/libng_test;
