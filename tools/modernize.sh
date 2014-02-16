IN_RCPP=`pwd | grep Rcpp11$`
if [ ${#IN_RCPP} == 0 ]; then
    echo "Error: not in base Rcpp11 directory."
    exit 0
fi;

## Put all of the header files into a file tool/modernize-include.txt
## Don't know know, why clang-modernize isn't happy when we just path
## the whole patch 'inst/include'
find inst/include -name "*.h" -type f > tools/modernize-include.txt

clang-modernize src/*.cpp \
    -include-from=tools/modernize-include.txt \
    -style="Chromium" \
    -risk=risky \
    -pass-by-value \
    -use-auto \
    -- \
    -std=c++1y \
    -Iinst/include \
    -I/Library/Frameworks/R.framework/Headers \
    -I/Users/kevinushey/.llvm/libcxx/include \
    -nostdinc++