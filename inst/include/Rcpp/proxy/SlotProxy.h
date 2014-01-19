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
        
        SlotProxy& operator=(const SlotProxy& rhs) ;
              
        template <typename T> SlotProxy& operator=(const T& rhs) ;
            
        template <typename T> operator T() const ;
        inline operator SEXP() const { 
            return get() ; 
        }
        
    private:
        CLASS& parent; 
        SEXP slot_name ;
            
        SEXP get() const ;
        void set(SEXP x ) ;
    } ;
    
    class const_SlotProxy : public GenericProxy<const_SlotProxy> {
    public:
        const_SlotProxy( const CLASS& v, const std::string& name) ;
        const_SlotProxy& operator=(const const_SlotProxy& rhs) ;
              
        template <typename T> operator T() const ;
        inline operator SEXP() const { 
            return get() ; 
        }
        
    private:
        const CLASS& parent; 
        SEXP slot_name ;
            
        SEXP get() const ;
    } ;
    
    SlotProxy slot(const std::string& name) ;
    const_SlotProxy slot(const std::string& name) const ;
    
} ;

}
#endif
