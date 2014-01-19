#ifndef Rcpp_Module_yes_h
#define Rcpp_Module_yes_h

inline bool yes( SEXP* /*args*/, int /* nargs */ ){
    return true ;
}

template<int n>
bool yes_arity( SEXP* /* args */ , int nargs){
    return nargs == n ;
}

#endif
