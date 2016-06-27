#!/bin/bash

cd src/src
rm *.csv
make clean
make 
./bloomfilters
rm ../../evaluation/*.pdf
../../evaluation/quality_nn.R
../../evaluation/quality_nn3.R
../../evaluation/cputime_nn.R
../../evaluation/cputime_nn3.R
../../evaluation/mem.R
../../evaluation/compl.R
