#ifndef Rcpp__vector__vector_from_string_h
#define Rcpp__vector__vector_from_string_h

namespace Rcpp{   
namespace internal{
    
    template <int RTYPE>
    SEXP vector_from_string( const std::string& st ) {
        return r_cast<RTYPE>( Rf_mkString( st.c_str() ) ) ;
    }
        
    template <int RTYPE>
    SEXP vector_from_string_expr( const std::string& code) {
        ParseStatus status;
        Shield<SEXP> expr = ::Rf_mkString( code.c_str() );
        Shield<SEXP> res  = ::R_ParseVector(expr, -1, &status, R_NilValue);
        switch( status ){
        case PARSE_OK:
            return(res) ;
            break;
        default:
            throw parse_error() ;
        }
        return R_NilValue ; /* -Wall */
    }
        
    template <>
    inline SEXP vector_from_string<EXPRSXP>( const std::string& st ) {
        return vector_from_string_expr<EXPRSXP>( st ) ;
    }
}
}

#endif
