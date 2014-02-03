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
            
            AttributeProxy& operator=(const AttributeProxy& rhs){
              set(rhs.get()) ; 
              return *this ;
            }
                  
            template <typename T> 
            AttributeProxy& operator=(const T& rhs){
              set(wrap(rhs));
              return *this ;
            }
                
            template <typename T> operator T() const {
              return as<T>(get());  
            }
            
            inline operator SEXP() const { 
                return get() ; 
            }
            
        private:
            CLASS& parent; 
            SEXP attr_name ;
                
            SEXP get() const {
              return Rf_getAttrib( parent, attr_name ) ;
            }
            void set(SEXP x ){
              Rf_setAttrib( parent, attr_name, x ) ;  
            }
        } ;
        
        class const_AttributeProxy : public GenericProxy<const_AttributeProxy> {
        public:
            const_AttributeProxy( const CLASS& v, const std::string& name)
              : parent(v), attr_name(Rf_install(name.c_str())){}
                  
            template <typename T> operator T() const {
              return as<T>(get());  
            }
            
            inline operator SEXP() const { 
                return get() ; 
            }
            
        private:
            const CLASS& parent; 
            SEXP attr_name ;
                
            SEXP get() const {
              return Rf_getAttrib( parent, attr_name ) ;
            }
        } ;
        
        AttributeProxy attr( const std::string& name) {
          return AttributeProxy( static_cast<CLASS&>(*this) , name ) ;
        }
        const_AttributeProxy attr( const std::string& name) const {
          return const_AttributeProxy( static_cast<const CLASS&>(*this) , name ) ;  
        }
        
    } ;

}
#endif
