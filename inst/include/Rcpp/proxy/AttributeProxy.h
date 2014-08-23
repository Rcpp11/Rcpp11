#ifndef Rcpp_AttributeProxy_h
#define Rcpp_AttributeProxy_h

namespace Rcpp{
    
    template <typename CLASS>
    class AttributeProxy : public GenericProxy<AttributeProxy<CLASS>> {
    public:
        AttributeProxy( CLASS& v, SEXP name ) 
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
        SEXP attr_name ;
            
        SEXP get() const {
          return Rf_getAttrib( parent, attr_name ) ;
        }
        void set(SEXP x ){
          Rf_setAttrib( parent, attr_name, x ) ;  
        }
    } ;
        
    template <typename CLASS>    
    AttributeProxy<CLASS> attr( CLASS& obj, const std::string& name) {
        return AttributeProxy<CLASS>( obj, Rf_install(name.c_str()) ) ;
    }
    
    template <typename CLASS>    
    const AttributeProxy<CLASS> attr( const CLASS& obj, const std::string& name) {
        return AttributeProxy<CLASS>( const_cast<CLASS&>(obj) , Rf_install(name.c_str()) ) ;  
    }
          
    inline bool has_attr( SEXP data, const std::string& attr) {
        SEXP attrs = ATTRIB(data);
        while( attrs != R_NilValue ){
            if( attr == CHAR(PRINTNAME(TAG(attrs))) ){
                return true ;
            }
            attrs = CDR( attrs ) ;
        }
        return false;    
    }
    
}
#endif
