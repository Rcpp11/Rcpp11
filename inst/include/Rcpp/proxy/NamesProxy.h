#ifndef Rcpp_proxy_NamesProxy_h
#define Rcpp_proxy_NamesProxy_h

namespace Rcpp{
    
    template <typename CLASS>
    class NamesProxy : public GenericProxy<NamesProxy<CLASS>> {
    public:
        NamesProxy( CLASS& v) : parent(v){} ;

        /* lvalue uses */              
        NamesProxy& operator=(const NamesProxy& rhs) {
            if( this != &rhs) set( rhs.get() ) ;
            return *this ;
        }

        template <typename T>
        NamesProxy& operator=(const T& rhs) {
            set( wrap( rhs ) ) ;
            return *this ;  
        }

        NamesProxy& operator=( std::initializer_list<const char*> ) ;
        
        template <typename T> operator T() const {
            return as<T>( get() ) ;  
        }
    
    private:
        CLASS& parent; 
    
        SEXP get() const {
            return RCPP_GET_NAMES(parent) ;
        }
    
        void set(SEXP x) {
            /* check if we can use a fast version */
            if( TYPEOF(x) == STRSXP && parent.size() == Rf_xlength(x) ){
                SEXP y = parent ; 
                Rf_setAttrib( y, R_NamesSymbol, x ) ;
            } else {
                /* use the slower and more flexible version (callback to R) */
                SEXP namesSym = Rf_install( "names<-" );
                parent = Rcpp_eval(Rf_lang3( namesSym, parent, x )) ;
            }
        
        }
        
    } ;

    template <typename CLASS>
    NamesProxy<CLASS> names(CLASS& obj) {
        return NamesProxy<CLASS>(obj) ;
    }
    
    template <typename CLASS>
    const NamesProxy<CLASS> names(const CLASS& obj) {
        return NamesProxy<CLASS>(const_cast<CLASS&>(obj) ) ;
    }

}

#endif
