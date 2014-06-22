#ifndef Rcpp_NameProxyPolicy_h
#define Rcpp_NameProxyPolicy_h

namespace Rcpp{
    
    template <typename CLASS>
    class NameProxy {
    public:
        NameProxy(CLASS& parent_, const std::string& name_): parent(parent_), name(name_){}
        
        template <typename T>
        inline operator T() const {
            return parent[ parent.offset(name) ] ;
        }
        
        template <typename T>
        inline CLASS& operator=( const T& rhs ){
            int index = 0 ;
            try{
                index = parent.offset(name) ;
                parent[ index ] = rhs ;
            } catch( ... ){
                int n = parent.size() ;
                CLASS v( n + 1 ) ;
                
                auto it = std::copy( parent.begin(), parent.end(), v.begin() );
                *it = rhs ;
                
                Shield<SEXP> names_ = Rf_allocVector(STRSXP, n+1) ;
                SEXP parent_names = names(parent) ;
                if( parent_names != R_NilValue ){
                    for( R_xlen_t i=0; i<n; i++){
                        SET_STRING_ELT( names_, i, STRING_ELT( parent_names, i ) ); 
                    }
                }
                SET_STRING_ELT( names_, n, Rf_mkChar(name.c_str()) );
                names(v) = names_ ;
                parent = std::move( v ) ;
            }
            return parent ;
        }
        
    private:
        CLASS& parent; 
        const std::string& name ;
    };
    
}    
    
#endif
