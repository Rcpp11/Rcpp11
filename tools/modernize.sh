#!/usr/bin/env sh

IN_RCPP=`pwd | grep Rcpp11$`
if [ ${#IN_RCPP} == 0 ]; then
    echo "Error: not in base Rcpp11 directory."
    exit 0
fi;

## Put all of the header files into a file tool/modernize-include.txt
## Don't know know, why clang-modernize isn't happy when we just path
## the whole patch 'inst/include'
find inst/include -name "*.h" -type f > tools/modernize-include.txt

## NOTE: For some reason, clang-modernize tries to add a second
## set of overrides to Rstreambuf.h, so we exclude it explicitly

## I also currently get assertion errors if I try to use 
## '-use-auto', hence I explicitly set some parameters for modernizing

clang-modernize src/*.cpp \
    -final-syntax-check \
    -include-from=tools/modernize-include.txt \
    -exclude="inst/include/Rcpp/iostream/Rstreambuf.h" \
    -style="Chromium" \
    -risk=risky \
    -pass-by-value \
    -loop-convert \
    -add-override \
    -for-compilers=clang-3.5 \
    -- \
    -std=c++1y \
    -I/Users/kevinushey/.llvm/libcxx/include \
    -I/Library/Frameworks/R.framework/Headers \
    -Iinst/include
    