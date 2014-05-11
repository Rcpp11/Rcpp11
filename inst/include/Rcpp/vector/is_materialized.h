#ifndef Rcpp__vector_is_materialized_h
#define Rcpp__vector_is_materialized_h

namespace Rcpp{
namespace traits{

    template <int RTYPE, typename Storage>
    struct is_materialized< Vector<RTYPE,Storage> >{
        typedef std::true_type type ;
    } ;
    
    template <int RTYPE, typename Storage>
    struct is_materialized< Matrix<RTYPE,Storage> >{
        typedef std::true_type type ;
    } ;
    
}
}
#endif
