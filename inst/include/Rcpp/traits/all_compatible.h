#ifndef Rcpp__traits__all_compatible__h
#define Rcpp__traits__all_compatible__h

namespace Rcpp{
    namespace traits{

        template <int RTYPE, typename... Args>
        struct all_compatible {
            typedef typename and_< typename is_compatible<RTYPE,typename std::decay<Args>::type >::type ... >::type type;
        } ;
        
    }
}
  
#endif
