// Copyright (C) 2013  Dirk Eddelbuettel and Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

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
            throw ::Rcpp::not_compatible( "not compatible with INTSXP" ) ;
        }
        return R_NilValue ; /* -Wall */
    }
    
    template<> inline SEXP r_true_cast<REALSXP>( SEXP x) {
        switch( TYPEOF( x ) ){
        case INTSXP:
        case LGLSXP:
        case CPLXSXP:
        case RAWSXP:
            return Rf_coerceVector( x, REALSXP );
        default:
            throw ::Rcpp::not_compatible( "not compatible with REALSXP" ) ;
        }
        return R_NilValue ; /* -Wall */
    }
    
    template<> inline SEXP r_true_cast<LGLSXP>( SEXP x) {
        switch( TYPEOF( x ) ){
        case REALSXP:
        case INTSXP:
        case CPLXSXP:
        case RAWSXP:
            return Rf_coerceVector( x, LGLSXP );
        default:
            throw ::Rcpp::not_compatible( "not compatible with LGLSXP" ) ;
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
            throw ::Rcpp::not_compatible( "not compatible with RAWSXP" ) ;
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
            throw ::Rcpp::not_compatible( "not compatible with CPLXSXP" ) ;
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
                Scoped<SEXP> call = Rf_lang2( Rf_install( "as.character" ), x ) ;
                Scoped<SEXP> res  = Rf_eval( call, R_GlobalEnv ) ;
                return res ;
            }
        case CHARSXP:
            return Rf_ScalarString( x ) ;
        case SYMSXP:
            return Rf_ScalarString( PRINTNAME( x ) ) ; 
        default:
            throw ::Rcpp::not_compatible( "not compatible with STRSXP" ) ;
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
                Scoped<SEXP> y = Rf_duplicate( x ); 
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
