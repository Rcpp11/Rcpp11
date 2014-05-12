#ifndef Rcpp_FieldProxy_h
#define Rcpp_FieldProxy_h

namespace Rcpp{
    
template <typename CLASS>
class FieldProxyPolicy {
public:
    
    class FieldProxy : GenericProxy<FieldProxy> {
    public:
        FieldProxy( CLASS& v, const std::string& name) : 
            parent(v), field_name( Rf_mkChar(name.c_str())) {}
        
        FieldProxy& operator=(const FieldProxy& rhs){
            set( rhs.get() ) ;
            return *this ;  
        }
              
        template <typename T> FieldProxy& operator=(const T& rhs) {
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
        SEXP field_name ;
            
        SEXP get() const {
            Shield<SEXP> call = Rf_lang3( 
                R_DollarSymbol, 
                parent, 
                Rf_ScalarString(field_name)
            ) ;
            return Rcpp_eval( call ) ;    
        }
        void set(SEXP x ){
            SEXP dollarGetsSym = Rf_install( "$<-");
            Shield<SEXP> name = Rf_ScalarString( field_name ) ;
            Shield<SEXP> call = Rf_lang4( 
                dollarGetsSym,
                parent, 
                name , 
                x
                );
            parent = Rf_eval( call, R_GlobalEnv ) ; 
        }
    } ;
    
    FieldProxy field(const std::string& name) {
        return FieldProxy( static_cast<CLASS&>(*this) , name ) ;  
    }
    const FieldProxy field(const std::string& name) const {
        return FieldProxy( const_cast<CLASS&>(static_cast<const CLASS&>(*this)) , name ) ;
    }
    
} ;

}
#endif
