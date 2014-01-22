#ifndef Rcpp__traits__any_named__h
#define Rcpp__traits__any_named__h

namespace Rcpp{
    namespace traits{
        
        template <typename... Args> 
        struct any_named {
            typedef typename or_< typename is_named<Args>::type ... >::type type;
        } ;
        
    }
}

#endif

