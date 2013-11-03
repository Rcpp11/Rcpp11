// Copyright (C) 2013 Romain Francois
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
