#ifndef Rcpp__traits__vector_of__h
#define Rcpp__traits__vector_of__h

namespace Rcpp{
    namespace traits{

        template <typename T>
        struct vector_of {
            typedef typename Vector< r_sexptype_traits<T>::rtype > type ;
        } ;
    }
}
#endif
