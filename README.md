Rcpp11
=======

[![Build Status](https://travis-ci.org/romainfrancois/Rcpp11.png)](https://travis-ci.org/romainfrancois/Rcpp11)

`Rcpp11` is a complete redesign of `Rcpp`, targetting C++11. 

Installing a C++11 compiler
=========================== 

Rcpp11 needs a C++11 capable compiler, it is known to work 
with clang 3.3 and gcc 4.8 on OSX and ubuntu. 

- This is trivial on OSX Mavericks if you have Xcode installed.  

I have this on my `~/.R/Makevars` file: 

```
CC=clang
CXX=clang++
CXXFLAGS= -stdlib=libc++ -std=c++11 -O3
CFLAGS=-g -O3 -Wall -pipe
```
            
- I have tested Rcpp11 with gcc 4.8 on ubuntu, e.g. here is what I do on travis to install g++ 4.8

```
  sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
  sudo apt-get update -qq
  sudo apt-get install -qq g++-4.8
```

Installation
============

Then, you can install it using `devtools::install_github`: 

```
devtools::install_github( "romainfrancois/Rcpp11" )
require( Rcpp11 )
evalCpp( "2LL" )
# [1] 2
```

