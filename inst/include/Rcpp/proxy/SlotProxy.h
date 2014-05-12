#ifndef Rcpp_SlotProxy_h
#define Rcpp_SlotProxy_h

namespace Rcpp{
    
template <typename CLASS>
class SlotProxyPolicy {
public:
    
    class SlotProxy : public GenericProxy<SlotProxy> {
    public:
        SlotProxy( CLASS& v, Symbol name) : 
            parent(v), slot_name(name) 
        {
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
        Symbol slot_name ;
            
        SEXP get() const {
            return R_do_slot( parent, slot_name ) ;
        }
        void set(SEXP x ) {
            parent = R_do_slot_assign(parent, slot_name, x);
        }
    } ;
    
    SlotProxy slot(const std::string& name) {
        SEXP x = ref() ;
        if( !Rf_isS4(x) ) throw not_s4() ;
        return SlotProxy( static_cast<CLASS&>(*this) , name ) ;
    }
    const SlotProxy slot(const std::string& name) const {
        SEXP x = ref() ;
        if( !Rf_isS4(x) ) throw not_s4() ;
        return SlotProxy( const_cast<CLASS&>(static_cast<const CLASS&>(*this)) , name ) ; 
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
