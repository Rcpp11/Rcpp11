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
  
* Added the concept of lazy vectors. A lazy vector is similar to a sugar 
  expression, but it only knows how to apply itself, i.e. we cannot 
  call `operator[](int)` on it. This is used for implementation of 
  `create` and `fuse`

* `create` can now also be used as a free function. For example: 
  `IntegerVector x = create(1,2,3) ;`. When used as a free function, `create` 
  chooses to create a lazy vector of the highest type. For example, 
  `create(1,2.0)` makes a lazy vector of type `REALSXP` (what makes sense for 
  `double`). 
  
* Added the `list` function. It takes a variadic list of arguments and makes an
  R list from it. This uses the same underlying implementation as `List::create`
  but is nicer to use. 
  
* `mapply` was reimplemented using variadic templates. `mapply` now accepts a 
  function as first parameter, then a variable number of sugar expressions. 

* `Array` gains a `fill` method to initialize all its data to the same value.    
  
* `is<>` was broken. 

* Initial implementation of `ListOf`. `ListOf<T>` is similar to `List` but 
  it only exposes constructors that take `T` objects and methods that maintain 
  this requirement. The implementation differs from Kevin Ushey's implementation 
  in Rcpp, which IMHO tries to do too much. 

# Rcpp11 3.1.0.1

* `Rcpp11` is now compatible with the gcc 4.6.3 as shipped by Rtools. Therefore
  `Rcpp11` is compatible with windows. 
