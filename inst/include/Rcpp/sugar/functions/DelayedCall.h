#ifndef Rcpp__sugar__DelayedCall_h
#define Rcpp__sugar__DelayedCall_h

namespace Rcpp{
    namespace sugar{
    
        template <typename OUT, typename FunctionType, typename... Args >
        class DelayedCall {
        public:
            typedef typename std::tuple<Args...> Tuple ;
            
            DelayedCall( FunctionType fun_, Args&&... args ): fun(fun_), data( std::forward<Args>(args)... ){}
            
            inline OUT operator()() const {
                return eval() ;
            }
            
            inline OUT eval() const {
                return invoke_dispatch( typename Rcpp::traits::index_sequence<Args...>::type() ) ;
            }
            
            template <int... S>
            inline OUT invoke_dispatch( Rcpp::traits::sequence<S...> ) const {
                return fun( std::get<S>(data) ... ) ;
            }
            
        private:
            size_t n ;
            FunctionType fun ;
            Tuple data ; 
        } ;
    
    
    } // sugar
    
    template <typename OUT, typename... Args>
    inline auto call( OUT (*fun)(Args...), Args&&... args ) -> sugar::DelayedCall<OUT,decltype(fun), Args...>{
        return sugar::DelayedCall<OUT,decltype(fun), Args...>( fun, std::forward<Args>(args) ... ) ;    
    }


} // Rcpp
#endif

