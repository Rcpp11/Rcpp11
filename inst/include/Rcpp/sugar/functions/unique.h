#ifndef Rcpp__sugar__unique_h
#define Rcpp__sugar__unique_h
          
namespace Rcpp{

template <int RTYPE, bool NA, typename T>
inline Vector<RTYPE> unique( const SugarVectorExpression<RTYPE,NA,T>& t ){
    typedef typename traits::storage_type<RTYPE>::type STORAGE;
    return wrap( std::unordered_set<STORAGE>( t.begin(), t.end() ) ) ;
}

template <int RTYPE, bool NA, typename T, bool RHS_NA, typename RHS_T>
inline LogicalVector in( const SugarVectorExpression<RTYPE,NA,T>& x, const SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& table ){
    typedef typename traits::storage_type<RTYPE>::type STORAGE;
    
    std::unordered_set<STORAGE> set( table.begin(), table.end() );
    LogicalVector res(x.size());
    std::transform( x.begin(), x.end(), res.begin(), [&set](STORAGE y){
            return set.count(y) ;
    }) ;
    return res ;
    
}


} // Rcpp
#endif

