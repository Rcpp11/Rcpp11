#ifndef Rcpp_Function_h
#define Rcpp_Function_h

namespace Rcpp{ 

    RCPP_API_CLASS(Function_Impl){
        RCPP_API_IMPL(Function_Impl)
        
        inline void set(SEXP x){
            switch( TYPEOF(x) ){
            case CLOSXP:
            case SPECIALSXP:
            case BUILTINSXP:
                data = x ;
                break; 
            default:
                throw not_compatible("cannot convert to function") ;
            }       
        }
        
        /**
         * Finds a function, searching from the global environment
         *
         * @param name name of the function
         */
        Function_Impl(const std::string& name) : 
            data( Rf_findFun( Rf_install( name.c_str() ), R_GlobalEnv ) ){}
       
        /**
         * calls the function with the specified arguments
         *
         * @param ...Args variable length argument list. The type of each 
         *        argument must be wrappable, meaning there need to be 
         *        a wrap function that takes this type as its parameter
         *
         */
        template<typename... Args> 
        SEXP operator()( const Args&... args) const {
            Shield<SEXP> call = language( data , args... ) ;
            return Rcpp_eval(call) ;
        }
        
        /**
         * Returns the environment of this function
         */
        SEXP environment() const {
            if( TYPEOF(data) != CLOSXP ) {
                throw not_a_closure() ;
            }
            return CLOENV(data) ;    
        }
        
        /**
         * Returns the body of the function
         */
        SEXP body() const {
            return BODY(data) ;    
        }
        
    };

} // namespace Rcpp

#endif
