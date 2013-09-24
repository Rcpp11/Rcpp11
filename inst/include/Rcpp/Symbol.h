//
// Symbol.h:  access R environments
//
// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Symbol_h
#define Rcpp_Symbol_h

#include <RcppCommon.h>
#include <Rcpp/RObject.h>

namespace Rcpp{ 

    class Symbol: public RObject{
    public:

        /**
         * wraps the SEXP into a Symbol object. 
         * 
         * @param m_sexp Accepted SEXP types are SYMSXP, CHARSXP and STRSXP
         * in the last case, the first element of the character vector 
         * is silently used
         */
        Symbol(SEXP x) ;
    
        /**
         *
         */
        Symbol(const std::string& symbol) ;
    
        Symbol( const Symbol& other) ;
        Symbol& operator=(const Symbol& other) ;
    
        /**
         * Nothing specific
         */ 
        ~Symbol() ;

        inline const char* c_str() const { return CHAR(PRINTNAME(m_sexp)) ; }
        
        inline bool operator==(const char* other) const { return ! strcmp(other, c_str() ); }
    };

} // namespace Rcpp

#endif
