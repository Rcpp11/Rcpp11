#ifndef Rcpp__sugar__lapply_h
#define Rcpp__sugar__lapply_h

namespace Rcpp{
    
    namespace sugar{
        
        template <typename Function>
        struct Wrapper{ 
            Wrapper(Function f_): f(f_){}
            
            template <typename T>
            inline SEXP operator()( T obj ) const {
                return wrap(f(obj));    
            }
            
            Function f ;
        } ;
        
    } // sugar
    
    template <int RTYPE, bool NA, typename T, typename Function >
    inline auto lapply( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t, Function fun ) -> decltype( sapply(t, sugar::Wrapper<Function>(fun) ) ) {
        return sapply( t, sugar::Wrapper<Function>(fun) );
    }

} // Rcpp

#endif
