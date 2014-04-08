#ifndef Rcpp_Promise_h
#define Rcpp_Promise_h

namespace Rcpp{ 
    
    RCPP_API_CLASS(Promise_Impl) {     
    public:
        RCPP_GENERATE_CTOR_ASSIGN(Promise_Impl) 

        Promise_Impl( SEXP x){
            if( TYPEOF(x) != PROMSXP )
                throw not_compatible("not a promise") ;
            
            while(TYPEOF(PRCODE(x)) == PROMSXP){
                x = PRCODE(x) ;
            }
            Storage::set__(x) ;
        }
        
        /** 
         * Return the result of the PRSEEN macro
         */
        int seen() const {
            return PRSEEN(Storage::get__());
        }
        
        /**
         * Return the result of the PRVALUE macro on the promise
         */
        SEXP value() const{
            SEXP val = PRVALUE(Storage::get__()) ; 
            if( val == R_UnboundValue ) throw unevaluated_promise() ;
            return val ;    
        }

        bool was_evaluated() const{
            return PRVALUE(Storage::get__()) != R_UnboundValue ;    
        }
        
        /**
         * The promise expression: PRCODE
         */
        SEXP expression() const {
            return PRCODE(Storage::get__());    
        }

        /**
         * The promise environment : PRENV
         */
        SEXP environment() const {
            return PRENV(Storage::get__());     
        }
        
    } ;

} // namespace

#endif
