#ifndef Rcpp__sugar__functional__negate_h
#define Rcpp__sugar__functional__negate_h

namespace Rcpp {
    namespace sugar {
        
        template <typename Callable>
        class Negate {
        private:
            Callable f ;
        
        public:
            Negate( Callable f_) : f(f_){}
            
            template <typename... Args>
            inline auto operator()( Args&&... args ) -> decltype( ! f( std::forward<Args>(args)... ) ) {
                return ! f( std::forward<Args>(args)... );    
            }
            
        } ;
        
    }
    
    template <typename Callable>
    sugar::Negate<Callable> negate( Callable f ){
        return sugar::Negate<Callable>(f) ;
    }
    
} // end namespace Rcpp


#endif 
