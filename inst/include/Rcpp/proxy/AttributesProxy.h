#ifndef Rcpp_proxy_AttributesProxy_h
#define Rcpp_proxy_AttributesProxy_h

namespace Rcpp{

  template <typename CLASS>
  class AttributesProxyPolicy {
  public:
    
    class AttributesProxy {
    public:
      AttributesProxy( CLASS& obj_ ) : obj(obj_){}
      
      template <typename... Args>
      void set( Args... args){
        obj = structure( obj, args... ) ;    
      }
      
    private:
      CLASS& obj ;
    } ;
    
    inline AttributesProxy attributes(){
      return AttributesProxy(static_cast<CLASS&>(*this)) ;  
    }
    
  } ;
  
}

#endif
