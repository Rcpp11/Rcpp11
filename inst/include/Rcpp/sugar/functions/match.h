#ifndef Rcpp__sugar__match_h
#define Rcpp__sugar__match_h
          
namespace Rcpp{

    template <int RTYPE, bool X_NA, typename T, bool RHS_NA, typename RHS_T>
    inline IntegerVector match( const SugarVectorExpression<RTYPE,X_NA,T>& x, const SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& table_ ){
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        
        std::unordered_map<STORAGE,int> map ;
        int i=0; 
        std::for_each( sugar_begin(table_), sugar_end(table_), [&]( STORAGE x ){
                ++i ;
                if( !map.count(x) ) map[x] = i ;
        }) ;
        
        IntegerVector res = transform( x.begin(), x.end(), [&map]( STORAGE x) -> int {
                if( map.count(x) ) return map.at(x) ;
                return NA ;
        }) ;
        
        return res ;
    }

} // Rcpp
#endif

