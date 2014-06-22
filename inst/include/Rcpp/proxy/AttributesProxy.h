#ifndef Rcpp_proxy_AttributesProxy_h
#define Rcpp_proxy_AttributesProxy_h

namespace Rcpp{

    template <typename CLASS>
    class AttributesProxy {
    public:
        AttributesProxy( CLASS& obj_ ) : obj(obj_){}
      
        template <typename... Args>
        void set( Args&&... args){
            obj = structure( obj, std::forward<Args>(args)... ) ;    
        }
        
        inline operator SEXP() const {
            return ATTRIB(obj) ;
        }
      
    private:
        CLASS& obj ;
    } ;
    
    template <typename CLASS>
    inline AttributesProxy<CLASS> attributes(CLASS& obj){
        return AttributesProxy<CLASS>(obj) ;  
    }
    
    template <typename CLASS>
    inline const AttributesProxy<CLASS> attributes(const CLASS& obj){
        return AttributesProxy<CLASS>(const_cast<CLASS&>(obj)) ;  
    }
    
}

#endif
