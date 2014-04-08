#ifndef Rcpp__traits__is_primitive__h
#define Rcpp__traits__is_primitive__h

namespace Rcpp{
namespace traits{

    template <typename T> struct is_primitive : public std::is_same<
        typename r_type_traits<T>::r_category , 
        r_type_primitive_tag
    >{} ;

} // traits
} // Rcpp

#endif
