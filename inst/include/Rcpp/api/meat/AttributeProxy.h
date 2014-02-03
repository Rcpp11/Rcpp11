#ifndef Rcpp_api_meat_AttributeProxy_h
#define Rcpp_api_meat_AttributeProxy_h

namespace Rcpp{

    
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
