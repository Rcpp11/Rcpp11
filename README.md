Rcpp11
=======

`Rcpp11` is an R package and a `C++11` library that dramatically facilitates integration of 
`R` and `C++11`.

`Rcpp11` will enforce `C++11` at the `configure` stage. 
Therefore it will not be published to CRAN until this distribution 
repository decides to finally allow `C++11`. 

`Rcpp11` will only be available on `github` during the initial cleaning stage involving:
 - removing code from `Rcpp` that should not be there but that is kept 
 in `Rcpp` because of too strong requirements, because it once was there, because someone 
somewhere might use it... For example the `RCPP_FUNCTION_..` macros that are 
 planned to be removed in july 2014 () in `Rcpp`. These macros will not be in `Rcpp11`.
 - the `Date` etc ... classes in `Rcpp` are using a design that is different 
 from all other classes of Rcpp, the proxy design. These classes will not be in `Rcpp11`. 
 Replacements might be included at a later stage if it is needed. Replacements should 
 follow the design principles of classes of the `Rcpp` API, e.g. `RObject`, ...
 - more emphasis on `C++11` features: e.g. initialisation lists and variadic templates will be used. 
 - `Rcpp11` will be able to assume features of `C++11`, for example move semantics, and therefore make active use of them: 
 packages depending on `Rcpp11` won't have to condition compile `C++11` availability. 
 - `Rcpp11` will try to use classes provided by `C++11` standard library, e.g. classes for regular expressions. 


Distribution
===========

Because `Rcpp11` cannot be on `CRAN` because `CRAN` insists on the `C++98` standard. 
I will have to find an alternative distribution repository. 

My goal is to setup this repository so that third party packages 
depending on `Rcpp11` can be published.

Installation
============

To install `Rcpp11` from github, you first need to get a compiler that supports `C++11`. 
- You should be fine with current releases of your linux distribution. 
- This is trivial on recent version of OSX. You can just use clang. 

I have this on my `~/.R/Makevars` file: 

```
CC=clang
CXX=clang++
PKG_CXXFLAGS= -stdlib=libc++ -std=c++11
```

Then, you can install it using `devtools::install_github`: 

```
devtools::install_github( "romainfrancois/Rcpp11" )
require( Rcpp11 )
evalCpp( "2LL" )
# [1] 2
```

