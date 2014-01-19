#ifndef Rcpp_api_meat_AttributeProxy_h
#define Rcpp_api_meat_AttributeProxy_h

namespace Rcpp{

    template <typename CLASS>
    typename AttributeProxyPolicy<CLASS>::AttributeProxy& AttributeProxyPolicy<CLASS>::AttributeProxy::operator=( const AttributeProxy& rhs ){
        set( rhs.get() ) ;
        return *this ;    
    }
    
    template <typename CLASS>
    SEXP AttributeProxyPolicy<CLASS>::AttributeProxy::get() const {
        return Rf_getAttrib( parent, attr_name ) ;    
    }
    
    template <typename CLASS>
    void AttributeProxyPolicy<CLASS>::AttributeProxy::set( SEXP x) {
        Rf_setAttrib( parent, attr_name, x ) ;
    }

    template <typename CLASS>
    typename AttributeProxyPolicy<CLASS>::AttributeProxy AttributeProxyPolicy<CLASS>::attr(const std::string& name) {
        return AttributeProxy( static_cast<CLASS&>(*this) , name ) ;
    }
 
    template <typename CLASS>
    template <typename T> 
    typename AttributeProxyPolicy<CLASS>::AttributeProxy& AttributeProxyPolicy<CLASS>::AttributeProxy::operator=( const T& rhs ){
        set( wrap( rhs ) ) ;
        return *this ;
    }
    
    template <typename CLASS>
    template <typename T>
    AttributeProxyPolicy<CLASS>::AttributeProxy::operator T() const {
        return as<T>(get()) ;    
    }

    
    
    template <typename CLASS>
    AttributeProxyPolicy<CLASS>::const_AttributeProxy::const_AttributeProxy( const CLASS& v, const std::string& name) 
        : parent(v), attr_name(Rf_install(name.c_str())){}

    template <typename CLASS>
    SEXP AttributeProxyPolicy<CLASS>::const_AttributeProxy::get() const {
        return Rf_getAttrib( parent, attr_name ) ;    
    }
    
    template <typename CLASS>
    typename AttributeProxyPolicy<CLASS>::const_AttributeProxy AttributeProxyPolicy<CLASS>::attr(const std::string& name) const {
        SEXP x = static_cast<const CLASS&>(*this) ;
        if( !Rf_isS4(x) ) throw not_s4() ;
        return const_AttributeProxy( static_cast<const CLASS&>(*this) , name ) ;
    }

    
}
#endif
