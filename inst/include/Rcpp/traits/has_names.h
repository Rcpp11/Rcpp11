#ifndef Rcpp__traits__has_names__h
#define Rcpp__traits__has_names__h

namespace Rcpp{
    namespace traits{
        
        template <typename... Args>
        struct has_names ;
        
        template <typename T, typename... Args> 
        struct has_names<T, Args...> {
            typedef typename Rcpp::traits::or_< 
                typename traits::is_named<T>::type, 
                typename has_names<Args...>::type
            >::type type;    
        } ;

        template <>
        struct has_names<>{
            typedef std::false_type type ;    
        } ;
        
    }
}

#endif

