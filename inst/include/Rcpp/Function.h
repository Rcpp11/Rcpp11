#ifndef Rcpp_Function_h
#define Rcpp_Function_h

namespace Rcpp{ 

    RCPP_API_CLASS(Function_Impl){
    public:

        RCPP_GENERATE_CTOR_ASSIGN(Function_Impl) 
	
        /**
         * Attempts to convert the SEXP to a pair list
         *
         * @throw not_compatible if the SEXP could not be converted
         * to a pair list using as.pairlist
         */
        Function_Impl(SEXP x = R_NilValue){
            RCPP_DEBUG( "Function::Function(SEXP = <%p>)", x)
            switch( TYPEOF(x) ){
            case CLOSXP:
            case SPECIALSXP:
            case BUILTINSXP:
                Storage::set__(x) ;
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
        Function_Impl(const std::string& name){
            SEXP nameSym = Rf_install( name.c_str() );	
            Storage::set__( Rf_findFun( nameSym, R_GlobalEnv ) ) ;
        }
       
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
            Shield<SEXP> call = language( Storage::get__() , args... ) ;
            return Rcpp_eval( call ) ;
        }
        
        /**
         * Returns the environment of this function
         */
        SEXP environment() const {
            if( TYPEOF(Storage::get__()) != CLOSXP ) {
                throw not_a_closure() ;
            }
            return CLOENV(Storage::get__()) ;    
        }
        
        /**
         * Returns the body of the function
         */
        SEXP body() const {
            return BODY( Storage::get__() ) ;    
        }
        
    };

} // namespace Rcpp

#endif
