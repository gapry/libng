#!/bin/sh

clea;
make clean;
make fmt; 
make test;
./build/test/gnet_test;
