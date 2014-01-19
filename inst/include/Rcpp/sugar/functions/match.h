#ifndef Rcpp__sugar__match_h
#define Rcpp__sugar__match_h
          
namespace Rcpp{

template <int RTYPE, bool NA, typename T, bool RHS_NA, typename RHS_T>
inline IntegerVector match( const VectorBase<RTYPE,NA,T>& x, const VectorBase<RTYPE,RHS_NA,RHS_T>& table_ ){
    Vector<RTYPE> table = table_ ;
    return sugar::IndexHash<RTYPE>( table ).fill().lookup( x.get_ref() ) ;
}

} // Rcpp
#endif

