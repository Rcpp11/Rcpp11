#ifndef Rcpp__sugar__rev_h
#define Rcpp__sugar__rev_h

namespace Rcpp{
    
    template <typename eT, typename Expr>
    inline sugar::Import< std::reverse_iterator<typename Expr::const_iterator> > rev( const SugarVectorExpression<eT, Expr>& t){
        typedef typename std::reverse_iterator<typename Expr::const_iterator> It ;
        return import( It(sugar_end(t)), It(sugar_begin(t)) ) ;
    }

} // Rcpp
#endif

