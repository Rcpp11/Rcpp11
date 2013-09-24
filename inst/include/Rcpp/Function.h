//
// Function.h:  functions (also primitives and builtins)
//
// Copyright (C) 2010 - 2012  Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013  Romain Francois
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

#ifndef Rcpp_Function_h
#define Rcpp_Function_h

#include <RcppCommon.h>

#include <Rcpp/grow.h>
#include <Rcpp/RObject.h>

namespace Rcpp{ 

    /** 
     * functions
     */
    class Function : public RObject{
    public:

        /**
         * Attempts to convert the SEXP to a pair list
         *
         * @throw not_compatible if the SEXP could not be converted
         * to a pair list using as.pairlist
         */
        Function(SEXP lang = R_NilValue) ;
        
        /**
         * Finds a function, searching from the global environment
         *
         * @param name name of the function
         */
        Function(const std::string& name) ;
        
        Function(const Function& other) ;
        Function& operator=(const Function& other );
        
        /**
         * calls the function with the specified arguments
         *
         * @param ...Args variable length argument list. The type of each 
         *        argument must be wrappable, meaning there need to be 
         *        a wrap function that takes this type as its parameter
         *
         */
        template<typename... Args> 
        SEXP operator()( const Args&... args) const {
            RCPP_DEBUG( "Function::operator(...) nargs = %d", sizeof...(args)  )
            SEXP call = PROTECT( Rcpp_lcons( m_sexp, pairlist(args...) ) ) ;
            SEXP res  = PROTECT( internal::try_catch( call ) ) ;
            RCPP_DEBUG( "res = <%p>", res  )
            UNPROTECT(2) ;
            return res ;
        }
        
        /**
         * Returns the environment of this function
         */
        SEXP environment() const ;
        
        /**
         * Returns the body of the function
         */
        SEXP body() const ;
         
        ~Function() ;
    };

} // namespace Rcpp

#endif
