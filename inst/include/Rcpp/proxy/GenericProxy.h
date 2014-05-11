#ifndef Rcpp_proxy_GenericProxy_h
#define Rcpp_proxy_GenericProxy_h

namespace Rcpp{
    
    template <typename Proxy>
    struct GenericProxy {
        inline SEXP get() const {
            return static_cast<const Proxy&>(*this) ;    
        }
    } ;

}

#endif
