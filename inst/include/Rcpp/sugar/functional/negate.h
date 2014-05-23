#ifndef Rcpp__sugar__functional__negate_h
#define Rcpp__sugar__functional__negate_h

namespace Rcpp {
    namespace functional {
        
        template <typename Callable>
        class Negate : public Functoid<Negate<Callable>> {
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
    functional::Negate<Callable> negate( Callable f ){
        return functional::Negate<Callable>(f) ;
    }
    
    template <typename T>
    functional::Negate<T> operator!( const functional::Functoid<T>& fun){
        return functional::Negate<T>( fun.get_ref() ) ;    
    }
    
} // end namespace Rcpp


#endif 
