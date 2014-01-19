#ifndef Rcpp__traits__sequence__h
#define Rcpp__traits__sequence__h
   
namespace Rcpp{
    namespace traits{
        
        template<int ...>
        struct sequence {};
        
        template<int N, int ...S> 
        struct gens : gens<N-1, N-1, S...> {};
        
        template<int ...S> 
        struct gens<0, S...>{ 
            typedef sequence<S...> type; 
        };
        
        template<typename... Args>
        struct index_sequence {
            typedef typename gens<sizeof...(Args)>::type type ;
        } ;
    }
}
#endif
