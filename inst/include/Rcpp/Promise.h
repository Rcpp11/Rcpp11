//
// Promise.h:  promises (PROMSXP)
//
// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Promise_h
#define Rcpp_Promise_h

#include <RcppCommon.h>
#include <Rcpp/Vector.h>
#include <Rcpp/Environment.h>
#include <Rcpp/RObject.h>

namespace Rcpp{ 
    class Promise : public RObject {     
    public:

        Promise( SEXP x);
        
        Promise( const Promise& other) ;
        Promise& operator=(const Promise& other ) ;
        
        Promise( Promise&& other) { 
            m_sexp = other.m_sexp ;
            other.m_sexp = R_NilValue ;
        }
        Promise& operator=( Promise&& other ){
            RCPP_DEBUG_CLASS( Promise, "::operator=( %s&& )", DEMANGLE(Promise) )
            if( this != &other ){
                Rcpp_ReleaseObject(m_sexp) ;
                m_sexp = other.m_sexp ;
                other.m_sexp = R_NilValue ;
            }
            return *this ;
        }

        /** 
         * Return the result of the PRSEEN macro
         */
        int seen() const ;
        
        /**
         * Return the result of the PRVALUE macro on the promise
         */
        SEXP value() const;

        bool was_evaluated() const ;
        
        /**
         * The promise expression: PRCODE
         */
        ExpressionVector expression() const ;

        /**
         * The promise environment : PRENV
         */
        Environment environment() const ;
        
    } ;

} // namespace

#endif
