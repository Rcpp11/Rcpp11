#ifndef Rcpp__sugar__unique_h
#define Rcpp__sugar__unique_h
          
namespace Rcpp{

    template <typename eT, typename Expr>
    inline typename traits::vector_of<eT>::type unique( const SugarVectorExpression<eT, Expr>& t ){
        std::unordered_set<eT> set( t.begin(), t.end() ) ;
        return import( set.begin(), set.end() ) ;
    }
    
    template <typename eT, typename Expr1, typename Expr2>
    inline LogicalVector in( const SugarVectorExpression<eT, Expr1>& x, const SugarVectorExpression<eT, Expr2>& table ){
        std::unordered_set<eT> set( table.begin(), table.end() );
        return transform( x.begin(), x.end(), [&set](STORAGE y) -> Rboolean {
                return set.count(y) ? TRUE : FALSE ;
        }) ;
    }

} // Rcpp
#endif

