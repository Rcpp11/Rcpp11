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

#ifndef Rcpp_S4_h
#define Rcpp_S4_h                     

namespace Rcpp{ 

    /**
     * S4 object
     */
    class S4 : RCPP_POLICIES(S4) {     
    public:
         
        S4(){}
        
        RCPP_GENERATE_CTOR_ASSIGN(S4) 
	    
        /**
         * checks that x is an S4 object and wrap it.
         *
         * @param x must be an S4 object
         */
        S4(SEXP x){
            set__(x) ;    
        }
        
        template <typename T> S4( const T& ) ;
        
        S4& operator=( SEXP other ) ; 
        
        /**
         * Creates an S4 object of the requested class. 
         *
         * @param klass name of the target S4 class
         * @throw not_s4 if klass does not map to a known S4 class
         */
        S4( const std::string& klass ) ;
        S4( const char* klass ) ; 
        
        /**
         * Indicates if this object is an instance of the given S4 class
         */
        bool is( const std::string& clazz) ;
        
        inline void update(SEXP x){
            if( ! ::Rf_isS4(x) ){
                throw not_s4() ;
            }
        }
        
    } ;

} // namespace Rcpp

#endif
