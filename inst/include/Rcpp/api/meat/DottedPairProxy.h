#ifndef Rcpp_api_meat_DottedPairProxy_h
#define Rcpp_api_meat_DottedPairProxy_h

namespace Rcpp{
     
    template <typename CLASS>
    template <typename T> 
    DottedPairProxyPolicy<CLASS>::DottedPairProxy::operator T() const {
        return as<T>(get());    
    }
    
    
    template <typename CLASS>
    template <typename T>
	  typename DottedPairProxyPolicy<CLASS>::DottedPairProxy& DottedPairProxyPolicy<CLASS>::DottedPairProxy::operator=(const traits::named_object<T>& rhs){
	      return set(wrap(rhs.object), rhs.name) ;
	  }
	
    template <typename CLASS>
    template <typename T>
    typename DottedPairProxyPolicy<CLASS>::DottedPairProxy& DottedPairProxyPolicy<CLASS>::DottedPairProxy::operator=(const T& rhs){
        return set(wrap(rhs)) ;    
    }
		
		
    template <typename CLASS>
    template <typename T> 
    DottedPairProxyPolicy<CLASS>::const_DottedPairProxy::operator T() const {
        return as<T>(get());    
    }
			
	
}

#endif                                         
