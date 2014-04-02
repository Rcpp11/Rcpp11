#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

template <int RTYPE, bool NA, typename T>
inline LogicalVector duplicated( const VectorBase<RTYPE,NA,T>& x ){
    Vector<RTYPE> vec(x) ;
    LogicalVector res(vec.size()) ;
    
    using STORAGE = typename traits::storage_type<RTYPE>::type ;
    std::unordered_set<STORAGE> set ;
    std::transform( vec.begin(), vec.end(), res.begin(), 
        [&set](STORAGE y){
            return !set.insert(y).second ;    
        }) ;
    
    return res ;
}


} // Rcpp
#endif

