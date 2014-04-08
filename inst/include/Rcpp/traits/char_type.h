#ifndef Rcpp__traits__char_type__h
#define Rcpp__traits__char_type__h

namespace Rcpp{
namespace traits{

    template <typename T>
    struct char_type {
        typedef typename T::value_type type ; 
    } ;

    template <> struct char_type< const wchar_t* > {
        typedef wchar_t type ;
    } ;
    template <> struct char_type< const char* > {
        typedef char type ;
    } ;
    
} // traits
} // Rcpp

#endif
