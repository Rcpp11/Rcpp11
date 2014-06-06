#ifndef Rcpp__sugar__match_h
#define Rcpp__sugar__match_h
          
namespace Rcpp{

    template <typename eT, typename Expr1, typename Expr2>
    inline IntegerVector match( const SugarVectorExpression<eT, Expr1>& x, const SugarVectorExpression<eT, Expr2>& table_ ){
        std::unordered_map<eT,int> map ;
        int i=0; 
        std::for_each( sugar_begin(table_), sugar_end(table_), [&]( eT x ){
                ++i ;
                if( !map.count(x) ) map[x] = i ;
        }) ;
        
        IntegerVector res = transform( x.begin(), x.end(), [&map]( eT x) -> int {
                if( map.count(x) ) return map.at(x) ;
                return NA ;
        }) ;
        
        return res ;
    }

} // Rcpp
#endif

