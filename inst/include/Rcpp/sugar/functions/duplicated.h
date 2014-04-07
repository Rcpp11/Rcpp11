#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

template <int RTYPE, bool NA, typename T>
inline LogicalVector duplicated( const VectorBase<RTYPE,NA,T>& x ){
    int n=x.size(); 
    LogicalVector res(n) ;
    
    using STORAGE = typename traits::storage_type<RTYPE>::type ;
    std::unordered_set<STORAGE> set ;
    for( int i=0; i<n; i++){
        res[i] = !set.insert(x[i]).second ;    
    }
    return res ;
}


} // Rcpp
#endif

