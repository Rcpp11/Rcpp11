#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

    template <typename eT, typename Expr>
    inline LogicalVector duplicated( const SugarVectorExpression<eT, Expr>& x ){
        int n = x.size(); 
        LogicalVector res(n) ;
        auto it = res.begin() ;
        std::unordered_set<eT> set ;
        for( R_xlen_t i=0; i<n; i++, ++it){
            *it = !set.insert(x[i]).second ? TRUE : FALSE ;    
        }
        return res ;
    }


} // Rcpp
#endif

