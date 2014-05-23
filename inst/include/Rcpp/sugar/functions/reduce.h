#ifndef Rcpp__sugar__functions__reduce_h
#define Rcpp__sugar__functions__reduce_h

namespace Rcpp {
    namespace sugar {
        
        template <int RTYPE, typename Expr, typename Callable>
        class Reduce {
        private:
            const Expr& expr ;
            Callable f ;
            
        public:
            typedef decltype( f(expr[0], expr[0]) ) result_type ;
            
        private:
            result_type value ;
        
        public:    
            Reduce( const Expr& expr_, Callable f_ ) : expr(expr_), f(f_) {
                auto it = sugar_begin(expr) ;
                auto init = *it ;
                ++it ;
                
                value = std::accumulate( it, sugar_end(expr), init, f )  ; 
            }
            
            inline result_type get() const {
                return value ;    
            }
            
            
        } ;
        
    }
    
    template <int RTYPE, bool NA, typename T, typename Callable>
    auto reduce( const SugarVectorExpression<RTYPE, NA, T>& data, Callable f) -> decltype( sugar::Reduce<RTYPE, SugarVectorExpression<RTYPE, NA, T>, Callable>(data, f).get() ) {
        return sugar::Reduce<RTYPE, SugarVectorExpression<RTYPE, NA, T>, Callable>(data, f).get() ;    
    }
    
    
} // end namespace Rcpp


#endif 
