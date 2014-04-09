#ifndef Rcpp__vector_is_materialized_h
#define Rcpp__vector_is_materialized_h

namespace Rcpp{
namespace traits{

    template <int RTYPE, template <class> class StoragePolicy>
    struct is_materialized< Vector<RTYPE,StoragePolicy> >{
        using type = std::true_type ;
    } ;
    
}
}
#endif
