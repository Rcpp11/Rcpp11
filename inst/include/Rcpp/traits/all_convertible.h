#ifndef Rcpp__traits__all_convertible__h
#define Rcpp__traits__all_convertible__h

namespace Rcpp{
    namespace traits{
    
        template <typename T, typename... Args>
        struct all_convertible : public and_< typename std::is_convertible<Args,T>::type ... >::type {} ;
        
    }
}

#endif
