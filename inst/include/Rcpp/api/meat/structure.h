#ifndef Rcpp_api_meat_structure_h
#define Rcpp_api_meat_structure_h

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
