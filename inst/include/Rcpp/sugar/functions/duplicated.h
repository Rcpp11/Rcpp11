#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

template <int RTYPE, bool NA, typename T>
inline LogicalVector duplicated( const SugarVectorExpression<RTYPE,NA,T>& x ){
    int n=x.size(); 
    LogicalVector res(n) ;
    
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;
    std::unordered_set<STORAGE> set ;
    for( R_xlen_t i=0; i<n; i++){
        res[i] = !set.insert(x[i]).second ? TRUE : FALSE ;    
    }
    return res ;
}


} // Rcpp
#endif

