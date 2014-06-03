#ifndef Rcpp__sugar__lapply_h
#define Rcpp__sugar__lapply_h

namespace Rcpp{
    
    namespace sugar{
        
        template <typename eT, typename Function>
        struct Wrapper{ 
            Wrapper(Function f_): f(f_){}
            
            inline SEXP operator()( eT obj ) const {
                return wrap(f(obj));    
            }
            
            Function f ;
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr, typename Function >
    inline auto lapply( const SugarVectorExpression<eT,Expr>& t, Function fun ) -> decltype( sapply(t, sugar::Wrapper<eT,Function>(fun) ) ) {
        return sapply( t, sugar::Wrapper<eT,Function>(fun) );
    }

} // Rcpp

#endif
