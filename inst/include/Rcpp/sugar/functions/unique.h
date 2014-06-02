#ifndef Rcpp__sugar__unique_h
#define Rcpp__sugar__unique_h
          
namespace Rcpp{

    template <typename Expr>
    inline typename traits::vector_of<typename Expr::value_type>::type unique( const SugarVectorExpression<Expr>& t ){
        typedef typename Expr::value_type value_type;
        std::unordered_set<value_type> set( t.begin(), t.end() ) ;
        return import( set.begin(), set.end() ) ;
    }
    
    template <typename Expr1, typename Expr2>
    inline typename std::enable_if<
        std::is_same< typename Expr1::value_type, typename Expr2::value_type >::value, 
        LogicalVector
    >::type in( const SugarVectorExpression<Expr1>& x, const SugarVectorExpression<Expr2>& table ){
        typedef typename Expr::value_type value_type ;
        
        std::unordered_set<value_type> set( table.begin(), table.end() );
        LogicalVector res = transform( x.begin(), x.end(), res.begin(), [&set](STORAGE y){
                return set.count(y) ;
        }) ;
        return res ;
    }

} // Rcpp
#endif

