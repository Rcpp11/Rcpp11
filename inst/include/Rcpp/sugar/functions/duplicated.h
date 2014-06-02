#ifndef Rcpp__sugar__duplicated_h
#define Rcpp__sugar__duplicated_h
          
namespace Rcpp{

    template <typename Expr>
    inline LogicalVector duplicated( const SugarVectorExpression<Expr>& x ){
        int n = x.size(); 
        LogicalVector res(n) ;
        
        typedef typename Expr::value_type STORAGE ;
        std::unordered_set<STORAGE> set ;
        for( R_xlen_t i=0; i<n; i++){
            res[i] = !set.insert(x[i]).second ? TRUE : FALSE ;    
        }
        return res ;
    }


} // Rcpp
#endif

