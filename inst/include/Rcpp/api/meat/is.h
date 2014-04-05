#ifndef Rcpp_api_meat_is_h
#define Rcpp_api_meat_is_h

namespace Rcpp{ 
namespace internal{
        
    template <>
    struct Is<RObject> {
        inline bool test(SEXP /* x */){ return true; }    
    } ;
    template <>
    struct Is<DataFrame> {
        inline bool test(SEXP x ){ 
            return Rf_inherits( x, "data.frame" ) ; 
        }    
    } ;
    template <>
    struct Is<S4> {
        inline bool test(SEXP x ){ 
            return  ::Rf_isS4(x); 
        }    
    } ;
    template <>
    struct Is<Reference> {
        inline bool test(SEXP x ){ 
            return ::Rf_inherits(x, "envRefClass" ) ; 
        }    
    } ;
    template <>
    struct Is<Formula> {
        inline bool test(SEXP x ){ 
            return Rf_inherits( x, "formula" ) ; 
        }    
    } ;
    template <>
    struct Is<Function> {
        inline bool test(SEXP x ){ 
            return TYPEOF(x) == CLOSXP || TYPEOF(x) == SPECIALSXP || TYPEOF(x) == BUILTINSXP ; 
        }    
    } ;
        
    
} // namespace internal
} // namespace Rcpp

#endif
