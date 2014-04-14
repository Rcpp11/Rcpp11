#ifndef Rcpp__traits__is_materialized__h
#define Rcpp__traits__is_materialized__h

namespace Rcpp{
namespace traits{

    template <typename T>
    struct is_materialized {
        typedef std::false_type type ;    
    }; 
    
}
}

#endif
