#ifndef Rcpp_internal_h
#define Rcpp_internal_h

#include <R_ext/Rdynload.h>

#define CALLFUN_0(name) SEXP name()
#define CALLFUN_1(name) SEXP name(SEXP)
#define CALLFUN_2(name) SEXP name(SEXP,SEXP)
#define CALLFUN_3(name) SEXP name(SEXP,SEXP,SEXP)
#define CALLFUN_4(name) SEXP name(SEXP,SEXP,SEXP,SEXP)
#define CALLFUN_5(name) SEXP name(SEXP,SEXP,SEXP,SEXP,SEXP)
#define EXTFUN(name) SEXP name(SEXP)

CALLFUN_1(rcpp_error_recorder);
CALLFUN_0(init_error_recorder);

#undef CALLFUN_0
#undef CALLFUN_1
#undef CALLFUN_2
#undef CALLFUN_3
#undef CALLFUN_4
#undef CALLFUN_5

#endif
