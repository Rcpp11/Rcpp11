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

CALLFUN_1(as_character_externalptr) ;

CALLFUN_1(Class__name);
CALLFUN_1(Class__has_default_constructor) ;

CALLFUN_1(CppClass__complete);
CALLFUN_1(CppClass__methods);

CALLFUN_1(Module__classes_info) ;
CALLFUN_1(Module__complete) ;
CALLFUN_1(Module__functions_arity);
CALLFUN_1(Module__functions_names);
CALLFUN_2(Module__get_class);
CALLFUN_2(Module__has_class);
CALLFUN_2(Module__has_function);
CALLFUN_2(Module__get_function);
CALLFUN_1(Module__name);
CALLFUN_2(CppObject__finalize);

CALLFUN_0(init_Rcpp11_cache);

CALLFUN_1(rcpp_error_recorder);

CALLFUN_3(CppField__get);
CALLFUN_4(CppField__set);
CALLFUN_0(init_error_recorder);

/* .External functions */
EXTFUN(CppMethod__invoke) ;
EXTFUN(CppMethod__invoke_void) ;
EXTFUN(CppMethod__invoke_notvoid) ;
EXTFUN(InternalFunction_invoke) ;
EXTFUN(Module__invoke) ;
EXTFUN(class__newInstance) ;
EXTFUN(class__dummyInstance) ;

void init_Rcpp11_routines(DllInfo*) ;
    

#undef CALLFUN_0
#undef CALLFUN_1
#undef CALLFUN_2
#undef CALLFUN_3
#undef CALLFUN_4
#undef CALLFUN_5

#define MAX_ARGS 65

#define UNPACK_EXTERNAL_ARGS(__CARGS__,__P__)    \
SEXP __CARGS__[MAX_ARGS] ;                       \
int nargs = 0 ;                                  \
for(; nargs<MAX_ARGS; nargs++){                  \
	if( __P__ == R_NilValue ) break ;            \
	__CARGS__[nargs] = CAR(__P__) ;              \
	__P__ = CDR(__P__) ;                         \
}

#define RCPP_FUN_1(__OUT__,__NAME__, ___0)        \
__OUT__ RCPP_DECORATE(__NAME__)(___0) ;               \
SEXP __NAME__(SEXP x0){                       \
SEXP res = R_NilValue ;                             \
BEGIN_RCPP                                          \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 )) ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)(___0)


#define RCPP_FUN_2(__OUT__,__NAME__, ___0, ___1)        \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1) ;               \
SEXP __NAME__(SEXP x0, SEXP x1){                       \
SEXP res = R_NilValue ;                             \
BEGIN_RCPP                                          \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 )) ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1)

#define RCPP_FUN_3(__OUT__,__NAME__, ___0, ___1, ___2)        \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2) ;               \
SEXP __NAME__(SEXP x0, SEXP x1, SEXP x2){                       \
SEXP res = R_NilValue ;                             \
BEGIN_RCPP                                          \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 ), ::Rcpp::internal::converter( x2 )) ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2)

#define RCPP_FUN_4(__OUT__,__NAME__, ___0, ___1, ___2, ___3)        \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2, ___3) ;               \
SEXP __NAME__(SEXP x0, SEXP x1, SEXP x2, SEXP x3){                       \
SEXP res = R_NilValue ;                             \
BEGIN_RCPP                                          \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 ), ::Rcpp::internal::converter( x2 ), ::Rcpp::internal::converter( x3 )) ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2, ___3)

#endif
