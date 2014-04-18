# Rcpp11 3.1.0.2

* sugar `sum` now supports complex sugar vector expressions

* sugar `mean` implements the double pass algorithm for `numeric`
  and `complex` cases (#134)

* more C++ support for Rcomplex: 
     `Rcomplex& operator+=( Rcomplex&, const Rcomplex& )`
     `Rcomplex operator/( Rcomplex, double )`
     
# Rcpp11 3.1.0.1

* `Rcpp11` is now compatible with the gcc 4.6.3 as shipped by Rtools. Therefore
  `Rcpp11` is compatible with windows. 
