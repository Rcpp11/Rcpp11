#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

    template <typename eT, typename Expr>
    inline LogicalVector duplicated( const SugarVectorExpression<eT, Expr>& x ){
        std::unordered_set<eT> set ;
        LogicalVector res( x.size() );
        std::transform( sugar_begin(x), sugar_end(x), res.begin(), [&](eT y){
                return set.insert(y).second ? FALSE : TRUE ;
        });
        return res ;
    }


} // Rcpp
#endif

