#ifndef Rcpp_api_meat_TagProxy_h
#define Rcpp_api_meat_TagProxy_h

namespace Rcpp{

    template <typename CLASS>
    template <typename U>
    typename TagProxyPolicy<CLASS>::TagProxy& TagProxyPolicy<CLASS>::TagProxy::operator=( const U& rhs ){
        set( wrap( rhs ) ) ;
        return *this ;
    }
    
    template <typename CLASS>
    template <typename U>
    TagProxyPolicy<CLASS>::TagProxy::operator U() const{
        return as<U>( get() ) ;
    }
    
    template <typename CLASS>
    template <typename U>
    TagProxyPolicy<CLASS>::const_TagProxy::operator U() const{
        return as<U>( get() ) ;
    }
    
}

#endif
