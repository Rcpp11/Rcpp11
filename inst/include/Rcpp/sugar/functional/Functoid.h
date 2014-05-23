#ifndef Rcpp__sugar__functional__functoid_h
#define Rcpp__sugar__functional__functoid_h

namespace Rcpp {
    namespace functional {
        
        struct FunctoidBase{} ;
        
        template <typename T>
        class Functoid : 
            public FunctoidBase, 
            public CRTP<T>
        {
        public:
            using CRTP<T>::get_ref ;
    
            template <typename... Args>
            inline auto operator()( Args&&... args) -> decltype( get_ref()(std::forward<Args>(args)...) ){
                return get_ref()(std::forward<Args>(args)...) ;
            }
            
        } ;
        
        template <typename T>
        class Capture : public Functoid<Capture<T>>{
        private:
            T fun ;
        
        public:
            Capture( T fun_) : fun(fun_){}
            
            template <typename... Args>
            inline auto operator()( Args&&... args) -> decltype( fun(std::forward<Args>(args)...) ){
                return fun(std::forward<Args>(args)...) ;
            }
        } ;
        
    }
    
    namespace traits {
        template <typename T>
        struct is_functoid {
            typedef typename std::is_base_of<Rcpp::functional::FunctoidBase, T>::type type ;    
        };
    }
    
} // end namespace Rcpp


#endif 
