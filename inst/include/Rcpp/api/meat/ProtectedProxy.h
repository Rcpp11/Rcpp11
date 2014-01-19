#ifndef Rcpp_api_meat_ProtectedProxy_h
#define Rcpp_api_meat_ProtectedProxy_h

namespace Rcpp{

    template <typename CLASS>
    template <typename U>
    typename ProtectedProxyPolicy<CLASS>::ProtectedProxy& ProtectedProxyPolicy<CLASS>::ProtectedProxy::operator=( const U& rhs ){
        set( wrap( rhs ) ) ;
        return *this ;
    }
    
    template <typename CLASS>
    template <typename U>
    ProtectedProxyPolicy<CLASS>::ProtectedProxy::operator U() const{
        return as<U>( get() ) ;
    }
    
    template <typename CLASS>
    template <typename U>
    ProtectedProxyPolicy<CLASS>::const_ProtectedProxy::operator U() const{
        return as<U>( get() ) ;
    }
    
}

#endif
