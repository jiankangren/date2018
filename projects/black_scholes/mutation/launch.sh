#!/bin/bash
set -x

#rm -rf output
clang-toolnumberone -v -debug -fun-op conf.csv -generate-mutants  ../src/BlackScholes.cpp -o output -- -std=c++11 -nocudainc -DTOOLNUMBERONE
