#ifndef Rcpp_RCPP_CHECK_BOUNDS_h
#define Rcpp_RCPP_CHECK_BOUNDS_h

#if defined(RCPP_DO_BOUNDS_CHECKS)
    #define RCPP_CHECK_BOUNDS(i) if( i<0 || i>= size() ) throw std::range_error("out of bounds") ;
#else
    #define RCPP_CHECK_BOUNDS(i)
#endif

#endif
