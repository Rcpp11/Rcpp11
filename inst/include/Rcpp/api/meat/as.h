#ifndef Rcpp_api_meat_as_h
#define Rcpp_api_meat_as_h

namespace Rcpp{
namespace internal{

    template <> inline Rcpp::String as<Rcpp::String>(SEXP x, ::Rcpp::traits::r_type_string_tag ) {
        if( ! Rf_isString(x) ){
            stop("expecting a string, got %s", type2name(x) ) ;
        }
        if (Rf_xlength(x) != 1) {
            stop("expecting a single value, git a vector of length %d", Rf_xlength(x) ) ;
        }
        return STRING_ELT( x, 0 ) ;
    }
    
}
}
#endif
