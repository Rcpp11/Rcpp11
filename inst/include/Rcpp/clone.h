#ifndef Rcpp_clone_h
#define Rcpp_clone_h

namespace Rcpp{ 

  template <typename T> 
  inline T clone(const T& object) {
      return T( Rf_duplicate( object ) ) ; 
  }

}
#endif
