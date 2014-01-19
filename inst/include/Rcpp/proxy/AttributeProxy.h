#ifndef Rcpp_AttributeProxy_h
#define Rcpp_AttributeProxy_h

namespace Rcpp{
    
    template <typename CLASS>
    class AttributeProxyPolicy {
    public:
        
        class AttributeProxy : public GenericProxy<AttributeProxy> {
        public:
            AttributeProxy( CLASS& v, const std::string& name) 
                : parent(v), attr_name(Rf_install(name.c_str()))
            {}
            
            AttributeProxy& operator=(const AttributeProxy& rhs) ;
                  
            template <typename T> AttributeProxy& operator=(const T& rhs) ;
                
            template <typename T> operator T() const ;
            
            inline operator SEXP() const { 
                return get() ; 
            }
            
        private:
            CLASS& parent; 
            SEXP attr_name ;
                
            SEXP get() const ;
            void set(SEXP x ) ;
        } ;
        
        class const_AttributeProxy : public GenericProxy<const_AttributeProxy> {
        public:
            const_AttributeProxy( const CLASS& v, const std::string& name) ;
            const_AttributeProxy& operator=(const const_AttributeProxy& rhs) ;
                  
            template <typename T> operator T() const ;
            
            inline operator SEXP() const { 
                return get() ; 
            }
            
        private:
            const CLASS& parent; 
            SEXP attr_name ;
                
            SEXP get() const ;
        } ;
        
        AttributeProxy attr( const std::string& name) ;
        const_AttributeProxy attr( const std::string& name) const ;
        
    } ;

}
#endif
