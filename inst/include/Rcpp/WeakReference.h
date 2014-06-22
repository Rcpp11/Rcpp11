#ifndef Rcpp_WeakReference_h
#define Rcpp_WeakReference_h

namespace Rcpp{

    RCPP_API_CLASS(WeakReference_Impl) {
        RCPP_API_IMPL(WeakReference_Impl)
    
        inline void set( SEXP x ){
            if( TYPEOF(x) != WEAKREFSXP )
                stop( "not a weak reference" ) ;
            data = x ;    
        }
        
        /** 
         * Retrieve the key
         */
        inline SEXP key() {
            return R_WeakRefKey(data) ;
        }

        /**
         * Retrieve the value
         */
        inline SEXP value(){
            return R_WeakRefValue(data);
        }

    } ;


}

#endif
