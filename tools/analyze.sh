#!/usr/bin/env sh

IN_RCPP=`pwd | grep Rcpp11$`
if [ ${#IN_RCPP} == 0 ]; then
    echo "Error: not in base Rcpp11 directory."
    exit 0
fi;

## Check the source files
clang-check src/*.cpp \
    -analyze \
    -- \
    -std=c++1y \
    -I/Users/kevinushey/.llvm/libcxx/include \
    -I/Library/Frameworks/R.framework/Headers \
    -Iinst/include
    
## Check Rcpp-test, if it's available
if [ -e ../Rcpp-test ]; then

    clang-check ../Rcpp-test/cpp/*.cpp \
        -analyze \
        -- \
        -std=c++1y \
        -I/Users/kevinushey/.llvm/libcxx/include \
        -I/Library/Frameworks/R.framework/Headers \
        -Iinst/include

fi;
