#!/usr/bin/env sh

IN_RCPP=`pwd | grep Rcpp11$`
if [ ${#IN_RCPP} == 0 ]; then
    echo "Error: not in base Rcpp11 directory."
    exit 0
fi;

## I also currently get assertion errors if I try to use 
## '-use-auto', hence I explicitly set some parameters for modernizing

clang-modernize src/*.cpp \
    -final-syntax-check \
    -include="inst/include" \
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
    