#ifndef RCPP_INTERNAL_COERCE_TRUECAST_H
#define RCPP_INTERNAL_COERCE_TRUECAST_H

namespace Rcpp{
namespace internal{
    
    template<> inline SEXP r_true_cast<INTSXP>(SEXP x) {
        switch( TYPEOF(x) ){
        case REALSXP:
        case RAWSXP:
        case LGLSXP:
        case CPLXSXP:
            return Rf_coerceVector( x, INTSXP) ;
        default:
            stop( "not compatible with INTSXP" ) ;
        }
        return R_NilValue ;
    }
    
    template<> inline SEXP r_true_cast<REALSXP>( SEXP x) {
        switch( TYPEOF( x ) ){
        case INTSXP:
        case LGLSXP:
        case CPLXSXP:
        case RAWSXP:
            return Rf_coerceVector( x, REALSXP );
        default:
            stop( "not compatible with REALSXP" ) ;
        }
        return R_NilValue ;
    }
    
    template<> inline SEXP r_true_cast<LGLSXP>( SEXP x) {
        switch( TYPEOF( x ) ){
        case REALSXP:
        case INTSXP:
        case CPLXSXP:
        case RAWSXP:
            return Rf_coerceVector( x, LGLSXP );
        default:
            stop( "not compatible with LGLSXP" ) ;
        }
        return R_NilValue ; /* -Wall */
    }
    
    template<> inline SEXP r_true_cast<RAWSXP>( SEXP x) {
        switch( TYPEOF( x ) ){
        case LGLSXP:
        case REALSXP:
        case INTSXP:
        case CPLXSXP:
            return Rf_coerceVector( x, RAWSXP );
        default:
            stop( "not compatible with RAWSXP" ) ;
        }
        return R_NilValue ; /* -Wall */
    }
    
    
    template<> inline SEXP r_true_cast<CPLXSXP>( SEXP x) {
        switch( TYPEOF( x ) ){
        case RAWSXP:
        case LGLSXP:
        case REALSXP:
        case INTSXP:
            return Rf_coerceVector( x, CPLXSXP );
        default:
            stop( "not compatible with CPLXSXP" ) ;
        }
        return R_NilValue ; /* -Wall */
    }
    
    template<> inline SEXP r_true_cast<STRSXP>( SEXP x) {
        switch( TYPEOF( x ) ){
        case CPLXSXP:
        case RAWSXP:
        case LGLSXP:
        case REALSXP:
        case INTSXP:
            {
                // return Rf_coerceVector( x, STRSXP );
                // coerceVector does not work for some reason
                Shield<SEXP> call = Rf_lang2( Rf_install( "as.character" ), x ) ;
                Shield<SEXP> res  = Rf_eval( call, R_GlobalEnv ) ;
                return res ;
            }
        case CHARSXP:
            return Rf_ScalarString( x ) ;
        case SYMSXP:
            return Rf_ScalarString( PRINTNAME( x ) ) ; 
        default:
            stop( "not compatible with STRSXP" ) ;
        }
        return R_NilValue ; /* -Wall */
    }
    
    template<> inline SEXP r_true_cast<VECSXP>(SEXP x) {
        return convert_using_rfunction(x, "as.list" ) ;
    }
    
    template<> inline SEXP r_true_cast<EXPRSXP>(SEXP x) {
        return convert_using_rfunction(x, "as.expression" ) ;
    }
    
    template<> inline SEXP r_true_cast<LISTSXP>(SEXP x) {
        switch( TYPEOF(x) ){
        case LANGSXP:
            {
                Shield<SEXP> y = Rf_duplicate( x ); 
                SET_TYPEOF(y,LISTSXP) ;
                return y ;
            }
        default:
            return convert_using_rfunction(x, "as.pairlist" ) ;
        }
    
    }
    
    template<> inline SEXP r_true_cast<LANGSXP>(SEXP x) {
        return convert_using_rfunction(x, "as.call" ) ;
    }
        
}
}

#endif
