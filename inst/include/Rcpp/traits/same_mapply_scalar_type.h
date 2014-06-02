#ifndef Rcpp__traits__same_mapply_scalar_type__h
#define Rcpp__traits__same_mapply_scalar_type__h

namespace Rcpp{
    namespace traits{
    
        template <typename T1, typename T2> 
        struct same_mapply_scalar_type : public std::is_same<
            typename mapply_scalar_type<T1>::type, 
            typename mapply_scalar_type<T2>::type
        >{} ;
    
    }
}

#endif
