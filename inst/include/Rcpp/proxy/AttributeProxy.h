#ifndef Rcpp_AttributeProxy_h
#define Rcpp_AttributeProxy_h

namespace Rcpp{
    
    template <typename CLASS>
    class AttributeProxyPolicy { 
    public:
        
        class AttributeProxy : public GenericProxy<AttributeProxy> {
        public:
            AttributeProxy( CLASS& v, Symbol name ) 
                : parent(v), attr_name(name)
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
            Symbol attr_name ;
                
            SEXP get() const {
              return Rf_getAttrib( parent, attr_name ) ;
            }
            void set(SEXP x ){
              Rf_setAttrib( parent, attr_name, x ) ;  
            }
        } ;
        
        class const_AttributeProxy : public GenericProxy<const_AttributeProxy> {
        public:
            const_AttributeProxy( const CLASS& v, Symbol name)
              : parent(v), attr_name(name){}
                  
            template <typename T> operator T() const {
              return as<T>(get());  
            }
            
            inline operator SEXP() const { 
                return get() ; 
            }
            
        private:
            const CLASS& parent; 
            Symbol attr_name ;
                
            SEXP get() const {
              return Rf_getAttrib( parent, attr_name ) ;
            }
        } ;
        
        AttributeProxy attr( const std::string& name) {
          return AttributeProxy( ref() , name ) ;
        }
        const_AttributeProxy attr( const std::string& name) const {
          return const_AttributeProxy( ref() , name ) ;  
        }
          
        bool hasAttribute( const std::string& attr) const {
            SEXP data = ref() ;
            SEXP attrs = ATTRIB(data);
            while( attrs != R_NilValue ){
                if( attr == CHAR(PRINTNAME(TAG(attrs))) ){
                    return true ;
                }
                attrs = CDR( attrs ) ;
            }
            return false;    
        }
        
        
    private:
        
        CLASS& ref(){
            return static_cast<CLASS&>(*this) ;    
        }
        
        const CLASS& ref() const{
            return static_cast<const CLASS&>(*this) ;    
        }
    
        
    } ;

}
#endif
