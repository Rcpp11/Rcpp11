#ifndef Rcpp_api_meat_FieldProxy_h
#define Rcpp_api_meat_FieldProxy_h

namespace Rcpp{

    template <typename CLASS>
    typename FieldProxyPolicy<CLASS>::FieldProxy& FieldProxyPolicy<CLASS>::FieldProxy::operator=( const FieldProxy& rhs ){
        set( rhs.get() ) ;
        return *this ;    
    }
    
    template <typename CLASS>
    SEXP FieldProxyPolicy<CLASS>::FieldProxy::get() const {
        Shield<SEXP> call = Rf_lang3( 
            R_DollarSymbol, 
            parent, 
            Rf_ScalarString(field_name)
        ) ;
        return Rcpp_eval( call ) ;    
    }
    
    template <typename CLASS>
    void FieldProxyPolicy<CLASS>::FieldProxy::set( SEXP x) {
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

    template <typename CLASS>
    typename FieldProxyPolicy<CLASS>::FieldProxy FieldProxyPolicy<CLASS>::field(const std::string& name) {
        return FieldProxy( static_cast<CLASS&>(*this) , name ) ;
    }
 
    template <typename CLASS>
    template <typename T> 
    typename FieldProxyPolicy<CLASS>::FieldProxy& FieldProxyPolicy<CLASS>::FieldProxy::operator=( const T& rhs ){
        set( wrap( rhs ) ) ;
        return *this ;
    }
    
    template <typename CLASS>
    template <typename T>
    FieldProxyPolicy<CLASS>::FieldProxy::operator T() const {
        return as<T>(get()) ;    
    }

    
    
    template <typename CLASS>
    FieldProxyPolicy<CLASS>::const_FieldProxy::const_FieldProxy( const CLASS& v, const std::string& name) 
        : parent(v), field_name(Rf_mkChar(name.c_str())){}

    template <typename CLASS>
    SEXP FieldProxyPolicy<CLASS>::const_FieldProxy::get() const {
        Shield<SEXP> call = Rf_lang3( 
            R_DollarSymbol, 
            parent, 
            Rf_ScalarString(field_name) 
        );
        return Rcpp_eval( call ) ;    
    }
    
    template <typename CLASS>
    typename FieldProxyPolicy<CLASS>::const_FieldProxy FieldProxyPolicy<CLASS>::field(const std::string& name) const {
        SEXP x = static_cast<const CLASS&>(*this) ;
        if( !Rf_isS4(x) ) throw not_s4() ;
        return const_FieldProxy( static_cast<const CLASS&>(*this) , name ) ;
    }

    
}
#endif
