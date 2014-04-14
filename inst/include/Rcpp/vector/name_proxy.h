#ifndef Rcpp__vector__name_proxy_h
#define Rcpp__vector__name_proxy_h

namespace Rcpp{
namespace internal{

    template <int RTYPE, typename VECTOR>
    class name_proxy {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type stored_type;
        
        void set( VECTOR& parent, const std::string& name, stored_type rhs ){
            int index = 0 ;
            try{
                index = parent.offset(name) ;
                parent[ index ] = rhs ;
            } catch( const index_out_of_bounds& /* ex */ ){
                int n = parent.size() ;
                VECTOR v( n + 1 ) ;
                
                std::copy( parent.begin(), parent.end(), v.begin() );
                v[n] = rhs ;
                
                Shield<SEXP> names = Rf_allocVector(STRSXP, n+1) ;
                SEXP parent_names = parent.names() ;
                if( parent_names != R_NilValue ){
                    for( int i=0; i<n; i++){
                        SET_STRING_ELT( names, i, STRING_ELT( parent_names, i ) ); 
                    }
                }
                SET_STRING_ELT( names, n, Rf_mkChar(name.c_str()) );
                v.names() = names ;
                parent = std::move( v ) ;
            }    
        }
        
    } ;
    
}
}

#endif
