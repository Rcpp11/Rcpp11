# Rcpp11 3.1.0.2

* sugar `sum` now supports complex sugar vector expressions

* sugar `mean` implements the double pass algorithm for `numeric`
  and `complex` cases (#134)

* more C++ support for Rcomplex: 
     `Rcomplex& operator+=( Rcomplex&, const Rcomplex& )`
     `Rcomplex operator/( Rcomplex, double )`

* Internal refactoring/simplification of all api classes. Api classes are now 
  parameterized by a class for the storage policy instead of a template 
  as before. 
  
* `Dots` and `NamedDots` handle the border case when `...` is missing (#123)

* If the macro `RCPP_DO_BOUNDS_CHECKS` is defined, vector classes will perform
  bounds checks. This is turned of by default because it kills performance. #141
  
* `Array` no longer generates spurious warnings. #154
  
# Rcpp11 3.1.0.1

* `Rcpp11` is now compatible with the gcc 4.6.3 as shipped by Rtools. Therefore
  `Rcpp11` is compatible with windows. 
