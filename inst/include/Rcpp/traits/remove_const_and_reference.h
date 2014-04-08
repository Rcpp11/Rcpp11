#ifndef Rcpp__traits__remove_const_and_reference__h
#define Rcpp__traits__remove_const_and_reference__h

namespace Rcpp{ namespace traits {

    template <typename T>
    struct remove_const_and_reference {
        typedef typename std::remove_const< typename std::remove_reference<T>::type >::type type ;
    } ;

}}

#endif
