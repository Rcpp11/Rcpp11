#ifndef Rcpp__structure__h
#define Rcpp__structure__h

namespace Rcpp{
 
  template <typename... Args>
  SEXP structure( SEXP obj, Args... args ){
      StretchyList attrs = ATTRIB(obj) ;
      
      attrs.set( args... ) ;
      SET_ATTRIB(obj, attrs) ;
      
      return obj ;
  }

}
#endif
