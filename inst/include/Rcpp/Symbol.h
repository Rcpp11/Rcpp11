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

    template < template <class> class StoragePolicy >
    class Symbol_Impl : 
        public StoragePolicy<Symbol_Impl<StoragePolicy>>    
    {
    public:
    
        RCPP_GENERATE_CTOR_ASSIGN__(Symbol_Impl) 
        
        /**
         * wraps the SEXP into a Symbol object. 
         * 
         * @param m_sexp Accepted SEXP types are SYMSXP, CHARSXP and STRSXP
         * in the last case, the first element of the character vector 
         * is silently used
         */
        Symbol_Impl(SEXP x){
            if( x != R_NilValue ){
                int type = TYPEOF(x) ;
                switch( type ){
                case SYMSXP:
                    Storage::set__( x ) ;
                    break; /* nothing to do */
                case CHARSXP: {
                    SEXP charSym = Rf_install(CHAR(x));     
                    Storage::set__( charSym ) ;
                    break ;
                }
                case STRSXP: {
                    /* FIXME: check that there is at least one element */
                    SEXP charSym = Rf_install( CHAR(STRING_ELT(x, 0 )) ); 
                    Storage::set__( charSym );
                    break ;
                }
                default:
                    throw not_compatible("cannot convert to symbol (SYMSXP)") ;
                }
            } 
        }
    
        /**
         *
         */
        Symbol_Impl(const std::string& symbol){
            Storage::set__(Rf_install(symbol.c_str()));
        }
    
        inline const char* c_str() const { 
            return CHAR(PRINTNAME(Storage::get__())) ;
        }
        
        inline bool operator==(const char* other) const { 
            return ! strcmp(other, c_str() );
        }
        
        void update(SEXP){}
    };

} // namespace Rcpp

#endif
