#ifndef Rcpp_WeakReference_h
#define Rcpp_WeakReference_h

namespace Rcpp{

    RCPP_API_CLASS(WeakReference_Impl) {
    public:
    
        RCPP_GENERATE_CTOR_ASSIGN(WeakReference_Impl) 

        /**
         * wraps a weak reference
         *
         * @param x presumably a SEXP of SEXTYPE WEAKREFSXP
         *
         * @throw not_compatible if x is not a weak reference
         */
        WeakReference_Impl( SEXP x){
            if( TYPEOF(x) != WEAKREFSXP )
                throw not_compatible( "not a weak reference" ) ;
            Storage::set__(x) ;
        }

        /** 
         * Retrieve the key
         */
        SEXP key() {
            return R_WeakRefKey(Storage::get__()) ;
        }

        /**
         * Retrieve the value
         */
        SEXP value(){
            return R_WeakRefValue(Storage::get__());
        }

    } ;


}

#endif
