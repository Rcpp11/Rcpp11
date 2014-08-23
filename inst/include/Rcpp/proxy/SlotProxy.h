#ifndef Rcpp_SlotProxy_h
#define Rcpp_SlotProxy_h

namespace Rcpp{
    
    template <typename CLASS>
    class SlotProxy : public GenericProxy<SlotProxy<CLASS>> {
    public:
        SlotProxy( CLASS& v, SEXP name) : 
            parent(v), slot_name(name) 
        {
            if( !R_has_slot( v, slot_name) ){
                stop("no such slot: %s", CHAR(PRINTNAME(name)) ) ; 
            }  
        }
        
        SlotProxy& operator=(const SlotProxy& rhs) {
            set( rhs.get() ) ;
            return *this ;
        }
              
        template <typename T> 
        SlotProxy& operator=(const T& rhs) {
            set( wrap( rhs ) ) ;
            return *this ;
        }
            
        template <typename T> operator T() const {
            return as<T>(get()) ;  
        }
        inline operator SEXP() const { 
            return get() ; 
        }
        
    private:
        CLASS& parent; 
        SEXP slot_name ;
            
        SEXP get() const {
            return R_do_slot( parent, slot_name ) ;
        }
        void set(SEXP x ) {
            parent = R_do_slot_assign(parent, slot_name, x);
        }
    } ;
    
    template <typename CLASS>
    SlotProxy<CLASS> slot(CLASS& x, const std::string& name) {
        if( !Rf_isS4(x) ) stop("not an S4 object");
        return SlotProxy<CLASS>(x, Rf_install(name.c_str()) ) ;
    }
    
    template <typename CLASS>
    const SlotProxy<CLASS> slot(const CLASS& x, const std::string& name) {
        if( !Rf_isS4(x) ) stop("not an S4 object");
        return SlotProxy<CLASS>( const_cast<CLASS&>(x) , Rf_install(name.c_str()) ) ; 
    }
    
    inline bool has_slot(SEXP data, const std::string& name) {
        if( !Rf_isS4(data) ) stop("not an S4 object");
        return R_has_slot( data, Rf_mkString(name.c_str()) ) ;    
    }
    
    inline bool isS4(SEXP data) { 
        return ::Rf_isS4(data) ; 
    }
    
}
#endif
