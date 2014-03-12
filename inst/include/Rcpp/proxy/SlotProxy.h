#ifndef Rcpp_SlotProxy_h
#define Rcpp_SlotProxy_h

namespace Rcpp{
    
template <typename CLASS>
class SlotProxyPolicy {
public:
    
    class SlotProxy : public GenericProxy<SlotProxy> {
    public:
        SlotProxy( CLASS& v, const std::string& name) : parent(v), slot_name(Rf_install(name.c_str())) {
            if( !R_has_slot( v, slot_name) ){
                throw no_such_slot() ; 
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
    
    class const_SlotProxy : public GenericProxy<const_SlotProxy> {
    public:
        const_SlotProxy( const CLASS& v, const std::string& name) 
          : parent(v), slot_name(Rf_install(name.c_str()))
        {
            if( !R_has_slot( v, slot_name) ){
                throw no_such_slot() ; 
            }        
        }
        
        template <typename T> operator T() const {
            return as<T>(get()) ;  
        }
        inline operator SEXP() const { 
            return get() ; 
        }
        
    private:
        const CLASS& parent; 
        SEXP slot_name ;
            
        SEXP get() const {
            return R_do_slot( parent, slot_name ) ;  
        }
    } ;
    
    SlotProxy slot(const std::string& name) {
        SEXP x = ref() ;
        if( !Rf_isS4(x) ) throw not_s4() ;
        return SlotProxy( static_cast<CLASS&>(*this) , name ) ;
    }
    const_SlotProxy slot(const std::string& name) const {
        SEXP x = ref() ;
        if( !Rf_isS4(x) ) throw not_s4() ;
        return const_SlotProxy( static_cast<const CLASS&>(*this) , name ) ; 
    }
    
    bool hasSlot(const std::string& name) const {
        SEXP data = ref() ;
        if( !Rf_isS4(data) ) throw not_s4() ;
        return R_has_slot( data, Rf_mkString(name.c_str()) ) ;    
    }
    
    inline bool isS4() const { 
        return ::Rf_isS4(ref()) ; 
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
