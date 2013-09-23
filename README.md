Rcpp11
=======

`Rcpp11` is an R package and a C++11 library that dramatically facilitates integration of 
`R` and `C++11`.

`Rcpp11` will enforce `C++11` at the `configure` stage. 
Therefore it will not be published to CRAN until this distribution 
repository decides to finally allow `C++11`. 

`Rcpp11` will only be available on `github` during the initial cleaning stage involving:
 - removing code from `Rcpp` that should not be there but that is kept 
 in `Rcpp` because of too strong requirements, because it once was there, because someone 
somewhere might use it... For example the `RCPP_FUNCTION_..` macros that are 
 planned to be removed in july 2014 () in `Rcpp`. These macros will not be in `Rcpp11`.
 - the `RcppDate` etc ... classes in `Rcpp` are using a design that is different 
 from all other classes of Rcpp, the proxy design. These classes will not be in `Rcpp11`. 
 Replacements might be included at a later stage if it is needed. Replacements should 
 follow the design principles of classes of the `Rcpp` API, e.g. `RObject`, ...
 - more emphasis on `C++11` features: e.g. initialisation lists and variadic templates will be used. 
 - `Rcpp11` will be able to assume features of C++11, for example move semantics, and therefore make active use of them: 
 packages depending on `Rcpp11` won't have to condition compile `C++11` availability. 
 - `Rcpp11` will try to use classes provided by C++11 standard library, e.g. classes for regular expressions. 


Distribution
===========

Because `Rcpp11` cannot be on `CRAN` because CRAN insists on (and even enforces) C++98, 
I will have to find an alternative distribution repository. 

My goal is to setup this repository so that third party packages depending on `Rcpp11` can be published.


What about Rcpp then ?
======================

I am no longer interested in being actively involved in Rcpp, 
which for several reasons has become too frustrating for me to work on. 

However, given I have some expertise on some aspects of Rcpp, 
I will still be available for development on Rcpp, on a contract basis. 

I am commited to `Rcpp11` and I seriously think that this is the way forward. 
C++11 is 2 years old. Complete compiler support is available. It is about
time we start using it.
