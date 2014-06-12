#ifndef Rcpp_proxy_RObjectMethods_h
#define Rcpp_proxy_RObjectMethods_h

namespace Rcpp{
    
    template <typename Class>
    class RObjectMethods {
    public:
        inline bool inherits(const char* clazz) const { 
            return ::Rf_inherits( ref(), clazz) ;
        }
                                                   
        inline bool isNULL() const{ return Rf_isNull(ref()) ; }
        inline bool isObject() const { return ::Rf_isObject(ref()) ;}
        
    private:
        
        Class& ref(){
            return static_cast<Class&>(*this) ;    
        }
        
        const Class& ref() const{
            return static_cast<const Class&>(*this) ;    
        }
        
    } ;
    
}

#endif
    
