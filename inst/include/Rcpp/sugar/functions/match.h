#ifndef Rcpp__sugar__match_h
#define Rcpp__sugar__match_h
          
namespace Rcpp{

    template <typename Expr1, typename Expr2>
    inline typename std::enable_if<
        traits::same_mapply_scalar_type<Expr1, Expr2>::value,
        IntegerVector
    >::type match( const SugarVectorExpression<Expr1>& x, const SugarVectorExpression<Expr2>& table_ ){
        
        typedef typename Expr1::value_type STORAGE ;
        
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

