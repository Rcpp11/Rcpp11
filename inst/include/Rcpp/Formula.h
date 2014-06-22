#ifndef Rcpp__Formula_h
#define Rcpp__Formula_h

namespace Rcpp{ 

    RCPP_API_CLASS(Formula_Impl), 
        public DottedPairProxyPolicy<Formula_Impl<Storage>>, 
        public DottedPairImpl<Formula_Impl<Storage>>
    {
        RCPP_API_IMPL(Formula_Impl)
        
        typedef typename DottedPairProxyPolicy<Formula_Impl<Storage>>::DottedPairProxy Proxy;
        
        inline void set(SEXP x){
            switch( TYPEOF( x ) ){
            case LANGSXP:
                if( ::Rf_inherits( x, "formula") ){
                    data = x ;
                } else{
                    data = internal::convert_using_rfunction( x, "as.formula") ;
                }
                break;
            case EXPRSXP:
            case VECSXP:
                /* lists or expression, try the first one */
                if( ::Rf_xlength(x) > 0 ){
                    SEXP y = VECTOR_ELT( x, 0 ) ;
                    if( ::Rf_inherits( y, "formula" ) ){
                        data = y ;  
                    } else{
                        data = internal::convert_using_rfunction( y, "as.formula") ;
                    }
                } else{
                    stop("cannot create formula from empty list or expression" ) ; 
                }
                break;
            default:
                data = internal::convert_using_rfunction( x, "as.formula") ;
            }
        }
        
        /**
         * Creates a call using the given symbol as the function name
         *
         * @param symbol symbol name to call
         *
         * Language( "rnorm" ) makes a SEXP similar to this (expressed in R)
         * > as.call( as.list( as.name( "rnorm") ) )
         * > call( "rnorm" )
         */
        explicit Formula_Impl( const std::string& code ): 
            data( internal::convert_using_rfunction( ::Rf_mkString(code.c_str()), "as.formula") ){}
        
        /**
         * eval this call in the global environment
         */
        SEXP eval() const {
            return eval( R_GlobalEnv ) ;    
        }

        /**
         * eval this call in the requested environment
         */
        SEXP eval(SEXP env) const {
            return Rcpp_eval( data, env ) ;
        }

    };

} // namespace Rcpp

#endif
