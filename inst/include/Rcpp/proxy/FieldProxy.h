// Copyright (C) 2013 - 2014 Romain Francois

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
        
        FieldProxy& operator=(const FieldProxy& rhs) ;
              
        template <typename T> FieldProxy& operator=(const T& rhs) ;
            
        template <typename T> operator T() const ;
        inline operator SEXP() const { return get() ; }
        
    private:
        CLASS& parent; 
        SEXP field_name ;
            
        SEXP get() const ;
        void set(SEXP x ) ;
    } ;
    
    class const_FieldProxy : GenericProxy<const_FieldProxy> {
    public:
        const_FieldProxy( const CLASS& v, const std::string& name) ;
        const_FieldProxy& operator=(const const_FieldProxy& rhs) ;
              
        template <typename T> operator T() const ;
        inline operator SEXP() const { return get() ; }
        
    private:
        const CLASS& parent; 
        SEXP field_name ;
            
        SEXP get() const ;
    } ;
    
    FieldProxy field(const std::string& name) ;
    const_FieldProxy field(const std::string& name) const ;
    
} ;

}
#endif
