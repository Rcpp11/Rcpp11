#ifndef Rcpp__sugar__can_have_na_h
#define Rcpp__sugar__can_have_na_h

namespace Rcpp{

template <typename T>
struct can_have_na :  T::can_have_na::type {} ;

} // Rcpp
#endif

