// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Reference_h
#define Rcpp_Reference_h                     

#include <Rcpp/S4.h>
#include <Rcpp/exceptions.h>

namespace Rcpp{ 

    /**
     * S4 object (of a reference class)
     */
    class Reference : public S4, public FieldProxyPolicy<Reference> {
    public:
        Reference() ;
        
        /**
         * checks that x is an S4 object of a reference class and wrap it.
         *
         * @param x must be an S4 object of some reference class
         */
        Reference(SEXP x) ; 
        
        /**
         * copy constructor
         *
         * @param other other S4 object
         */
        Reference(const Reference& other) ;
        
        template <typename T>
        Reference(const T& object ) ;
        
        Reference& operator=( const Reference& other);
        Reference& operator=( SEXP other ) ; 
        
        /**
         * Creates an reference object of the requested class. 
         *
         * @param klass name of the target reference class
         * @throw reference_creation_error if klass does not map to a known S4 class
         */
        Reference( const std::string& klass ) ;
        Reference( const char* klass ) ;

    private:
        void set_sexp( SEXP x) ;
        void check() ;        
    } ;

} // namespace Rcpp

#endif
