#ifndef Rcpp__structure__h
#define Rcpp__structure__h

namespace Rcpp{
 
  template <typename... Args>
  SEXP structure( SEXP obj, Args&&... args ) ;

}
#endif
