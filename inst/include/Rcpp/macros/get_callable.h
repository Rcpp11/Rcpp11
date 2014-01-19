#ifndef Rcpp_macros_get_callable_h
#define Rcpp_macros_get_callable_h

#define GET_CALLABLE(__FUN__)                               \
typedef decltype(__FUN__)* Fun ;                            \
static Fun fun = (Fun)R_GetCCallable( "Rcpp11", #__FUN__)   \

#endif
