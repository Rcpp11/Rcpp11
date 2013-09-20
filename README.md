Rcpp11
=======

This is a fork of Rcpp specialised in c++11, the current c++ standard. 
Rcpp11 will also aim at more progressive features than Rcpp thy has its hands tied by CRAN and too strong backward compatibility requirements. 

Rcpp11 will enforce c++11 at the configure stage. Therefore it will not be publish to cran until cran decides to allow c++11. 

Rcpp11 will only be available on github during the initial cleaning stage involving:
- removing code from Rcpp that should not be there but tht is kept in Rcpp because of too strong requirements. For example the RCPP_FUNCTION_.. macros that are planned to be removed in july 2014 in Rcpp. These macros will not be in Rcpp11.
- the date classes in Rcpp uses a design that is different from all other classes of Rcpp. These classes will not be in Rcpp11
- more emphasis on c++11 features: e.g. initialisation lists and variadic trmplates will be used. 
- Rcpp11 will be able to assume features of c++11, for example move constructors. 
- Rcpp11 will try to use classes provided by c++11 standard library, e.g. Classes for regular expressions. 


Distribtion
===========

Because Rcpp11 cańt be on CRAN because CRAN insists (enforces even) c++98, i will have to find an alternative distribution repository. My goal is to setup this repository so that third party packages depending on Rcpp11 can be published.

What about Rcpp then ?
======================

I'm sure Dirk will keep supporting Rcpp on CRAN and r-forge. 

I am no longer interested in being actively involved in Rcpp, which for several reasons has become too frustrating to work on. 

However, given I have some expertise on some aspects of Rcpp, I will still be available for development on Rcpp, on a contract basis. 

I am commited to Rcpp11 an i serioysly think that this is the way forward. C++11 is 2 years old. It is about time we start using it. 


