//
// RObject.h:  general R object wrapper
//
// Copyright (C) 2009 - 2012    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_RObject_h
#define Rcpp_RObject_h

namespace Rcpp{ 

    class RObject : RCPP_POLICIES(RObject) {
    public:
        
        /**
         * default constructor. uses R_NilValue
         */ 
        RObject() {}

        RCPP_GENERATE_CTOR_ASSIGN(RObject) 
        
        /**
         * wraps a SEXP. The SEXP is automatically protected from garbage 
         * collection by this object and the protection vanishes when this 
         * object is destroyed
         */
        RObject(SEXP x) {
            set__(x) ;    
        }

        /** 
         * Assignement operator. Set this SEXP to the given SEXP
         */ 
        RObject& operator=( SEXP other ) ;
        
        void update(SEXP){}
   };

} // namespace Rcpp

#endif
