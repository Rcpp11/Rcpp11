#ifndef Rcpp_api_meat_NamesProxy_h
#define Rcpp_api_meat_NamesProxy_h

namespace Rcpp{

    template <typename CLASS>
    template <typename T>                                                                                 
    typename NamesProxyPolicy<CLASS>::NamesProxy& NamesProxyPolicy<CLASS>::NamesProxy::operator=( const T& rhs ){
        set( wrap( rhs ) ) ;
        return *this ;
    }
    
    template <typename CLASS>
    template <typename T>                                                                                 
    NamesProxyPolicy<CLASS>::NamesProxy::operator T() const {
        return as<T>( get() ) ;    
    }
    
    template <typename CLASS>
    template <typename T>                                                                                 
    NamesProxyPolicy<CLASS>::const_NamesProxy::operator T() const {
        return as<T>( get() ) ;    
    }
    
    
}

#endif
    
