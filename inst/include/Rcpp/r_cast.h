#ifndef Rcpp_rcast_h
#define Rcpp_rcast_h

namespace Rcpp{
    namespace internal {
        
        inline SEXP convert_using_rfunction(SEXP x, const char* const fun) {
            SEXP res = R_NilValue ;
            try{
                SEXP funSym = Rf_install(fun);
                res = Rcpp_eval( Rf_lang2( funSym, x ) ) ;
            } catch( ... ){
                stop("could not convert using R function '%s' ", fun) ;
            }
            return res;
        }
        
        // r_true_cast is only meant to be used when the target SEXP type
        // is different from the SEXP type of x 
        template <int TARGET>
        SEXP r_true_cast( SEXP /* x */) {
            stop( "not compatible" ) ;
        }

        template<> SEXP r_true_cast<INTSXP>(SEXP x) ;
        template<> SEXP r_true_cast<REALSXP>(SEXP x) ;
        template<> SEXP r_true_cast<RAWSXP>(SEXP x) ;
        template<> SEXP r_true_cast<CPLXSXP>(SEXP x) ;
        template<> SEXP r_true_cast<LGLSXP>(SEXP x) ;
        template<> SEXP r_true_cast<STRSXP>(SEXP x) ;
        template<> SEXP r_true_cast<VECSXP>(SEXP x) ;
        template<> SEXP r_true_cast<EXPRSXP>(SEXP x) ;
        template<> SEXP r_true_cast<LISTSXP>(SEXP x) ;
        template<> SEXP r_true_cast<LANGSXP>(SEXP x) ;

    } // namespace internal 

    template <int TARGET> SEXP r_cast( SEXP x) { 
        return (TYPEOF(x)== TARGET) ? x : internal::r_true_cast<TARGET>(x) ; 
    }

} // namespace Rcpp

#endif
