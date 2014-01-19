#ifndef Rcpp_api_meat_NodeProxy_h
#define Rcpp_api_meat_NodeProxy_h

namespace Rcpp{
  
  template <typename CLASS>
  template <typename T>
  typename NodeProxyPolicy<CLASS>::ValueProxy&  NodeProxyPolicy<CLASS>::ValueProxy::operator=( const T& rhs){
      return set( wrap(rhs) );
  }
  
  template <typename CLASS>
  template <typename T>
  NodeProxyPolicy<CLASS>::ValueProxy::operator T() const {
      return as<T>(get());
  }
  
  template <typename CLASS>
  template <typename T>
  NodeProxyPolicy<CLASS>::const_ValueProxy::operator T() const {
      return as<T>(get());
  }
  
}

#endif
