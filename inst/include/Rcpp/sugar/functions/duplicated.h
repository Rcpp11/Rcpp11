#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

template <int RTYPE, bool NA, typename T>
inline LogicalVector duplicated( const VectorBase<RTYPE,NA,T>& x ){
    Vector<RTYPE> vec(x) ;
    sugar::IndexHash<RTYPE> hash(vec) ;
    return hash.fill_and_get_duplicated() ;
}


} // Rcpp
#endif

