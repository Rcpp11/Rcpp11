#ifndef Rcpp_NameProxyPolicy_h
#define Rcpp_NameProxyPolicy_h

namespace Rcpp{
    
    template <typename CLASS>
    class NameProxyPolicy { 
    public:

        class NameProxy {
        public:
            NameProxy(CLASS& parent_, const std::string& name_): parent(parent_), name(name_){}
            
            template <typename T>
            inline operator T() const {
                auto res = parent[ parent.offset(name) ] ;
                return res ;
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
                    
                    std::copy( parent.begin(), parent.end(), v.begin() );
                    v[n] = rhs ;
                    
                    Shield<SEXP> names = Rf_allocVector(STRSXP, n+1) ;
                    SEXP parent_names = parent.names() ;
                    if( parent_names != R_NilValue ){
                        for( R_xlen_t i=0; i<n; i++){
                            SET_STRING_ELT( names, i, STRING_ELT( parent_names, i ) ); 
                        }
                    }
                    SET_STRING_ELT( names, n, Rf_mkChar(name.c_str()) );
                    v.names() = names ;
                    parent = std::move( v ) ;
                }
                return parent ;
            }
            
        private:
            CLASS& parent; 
            const std::string& name ;
        };
        
        inline NameProxy operator[]( const std::string& name){
            return NameProxy( static_cast<CLASS&>(*this), name ) ;
        }
        
        inline const NameProxy operator[]( const std::string& name) const {
            return NameProxy( const_cast<CLASS&>(static_cast<const CLASS&>(*this)), name ) ;
        }
        
    } ;
}    
    
#endif
