#ifndef Rcpp_Promise_h
#define Rcpp_Promise_h

namespace Rcpp{ 
    
    RCPP_API_CLASS(Promise_Impl) {     
    public:
        RCPP_API_IMPL(Promise_Impl) 
        
        inline void set(SEXP x){
            if( TYPEOF(x) != PROMSXP )
                throw not_compatible("not a promise") ;
            
            while(TYPEOF(PRCODE(x)) == PROMSXP){
                x = PRCODE(x) ;
            }
            data = x ;    
        }
        
        /** 
         * Return the result of the PRSEEN macro
         */
        int seen() const {
            return PRSEEN(data);
        }
        
        /**
         * Return the result of the PRVALUE macro on the promise
         */
        SEXP value() const{
            SEXP val = PRVALUE(data) ; 
            if( val == R_UnboundValue ) throw unevaluated_promise() ;
            return val ;    
        }

        bool was_evaluated() const{
            return PRVALUE(data) != R_UnboundValue ;    
        }
        
        /**
         * The promise expression: PRCODE
         */
        SEXP expression() const {
            return PRCODE(data);    
        }

        /**
         * The promise environment : PRENV
         */
        SEXP environment() const {
            return PRENV(data);     
        }
        
    } ;

} // namespace

#endif
