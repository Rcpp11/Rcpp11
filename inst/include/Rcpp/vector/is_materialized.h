#ifndef Rcpp__vector_is_materialized_h
#define Rcpp__vector_is_materialized_h

namespace Rcpp{
namespace traits{

    template <int RTYPE, template <class> class StoragePolicy>
    struct is_materialized< Vector<RTYPE,StoragePolicy> >{
        typedef std::true_type type ;
    } ;
    
    template <int RTYPE, template <class> class StoragePolicy>
    struct is_materialized< Matrix<RTYPE,StoragePolicy> >{
        typedef std::true_type type ;
    } ;
    
}
}
#endif
