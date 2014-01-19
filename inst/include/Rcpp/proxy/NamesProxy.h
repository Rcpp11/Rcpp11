#ifndef Rcpp_proxy_NamesProxy_h
#define Rcpp_proxy_NamesProxy_h

namespace Rcpp{
    
template <typename CLASS>
class NamesProxyPolicy{
public:
    
    class NamesProxy : public GenericProxy<NamesProxy> {
    public:
        NamesProxy( CLASS& v) : parent(v){} ;
	
        /* lvalue uses */              
        NamesProxy& operator=(const NamesProxy& rhs) {
            if( this != &rhs) set( rhs.get() ) ;
            return *this ;
        }
	
        template <typename T>
        NamesProxy& operator=(const T& rhs) ;
	
        template <typename T> operator T() const ;
		
    private:
        CLASS& parent; 
		
        SEXP get() const {
            return RCPP_GET_NAMES(parent.get__()) ;
        }
		
        void set(SEXP x) {
            /* check if we can use a fast version */
            if( TYPEOF(x) == STRSXP && parent.size() == Rf_length(x) ){
                SEXP y = parent.get__() ; 
                Rf_setAttrib( y, R_NamesSymbol, x ) ;
            } else {
                /* use the slower and more flexible version (callback to R) */
                SEXP namesSym = Rf_install( "names<-" );
                Shield<SEXP> new_vec( Rcpp_eval(Rf_lang3( namesSym, parent, x ))) ;
                parent.set__(new_vec); 
            }
    		
        }
    		
    } ;

    class const_NamesProxy : public GenericProxy<const_NamesProxy>{
    public:
        const_NamesProxy( const CLASS& v) : parent(v){} ;
	
        template <typename T> operator T() const ;
		
    private:
        const CLASS& parent; 
		
        SEXP get() const {
            return RCPP_GET_NAMES(parent.get__()) ;
        }
		
    } ;

    NamesProxy names() {
        return NamesProxy( static_cast<CLASS&>(*this) ) ;
    }
    
    const_NamesProxy names() const {
        return const_NamesProxy(static_cast<const CLASS&>(*this) ) ;
    }
    
    
} ;

}

#endif
