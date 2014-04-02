#ifndef Rcpp__sugar__match_h
#define Rcpp__sugar__match_h
          
namespace Rcpp{

template <int RTYPE, bool NA, typename T, bool RHS_NA, typename RHS_T>
inline IntegerVector match( const VectorBase<RTYPE,NA,T>& x, const VectorBase<RTYPE,RHS_NA,RHS_T>& table_ ){
    Vector<RTYPE> table = table_ ;
    using STORAGE = typename traits::storage_type<RTYPE>::type ;
    std::unordered_map<STORAGE,int> map ;
    int n=table.size() ;
    for( int i=0; i<n; i++){
        if( !map.count(table[i]) ) map[table[i]] = i+1 ;    
    }
    
    n = x.size() ;
    IntegerVector res(n) ;
    std::transform( x.begin(), x.end(), res.begin(), [&map]( STORAGE x) -> int {
            if( map.count(x) ) return map.at(x) ;
            return NA_INTEGER ;
    }) ;
    
    return res ;
}

} // Rcpp
#endif

