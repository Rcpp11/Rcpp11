#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

    template <typename eT, typename Expr>
    inline LogicalVector duplicated( const SugarVectorExpression<eT, Expr>& x ){
        std::unordered_set<eT> set ;
        LogicalVector res = transform( sugar_begin(x), sugar_end(x), [&set](eT y){
                return ! set.insert(y).second ? TRUE : FALSE ;
        });
        return res ;
    }


} // Rcpp
#endif

