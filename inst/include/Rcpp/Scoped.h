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

#ifndef Rcpp__Scoped_h
#define Rcpp__Scoped_h

namespace Rcpp{
    
    inline SEXP Rcpp_protect(SEXP x){
        if( x != R_NilValue ) PROTECT(x) ; 
        return x ; 
    }
    
    template <typename T>
    class Scoped{
    public:
        Scoped( SEXP t_) : t(Rcpp_protect(t_)){}
        ~Scoped(){
            if( t != R_NilValue ) UNPROTECT(1) ;    
        }
        Scoped( const Scoped& ) = delete ;
        Scoped& operator=( const Scoped& ) = delete ;
        
        Scoped( Scoped&& other ) : t(other.t) {
            other.t = R_NilValue ;
        }
        Scoped& operator=( Scoped&& other ){
            t = other.t ;
            other.t = R_NilValue ;
            return *this ;
        }
        
        operator SEXP() const { return t; }
        SEXP t ;
    } ;
    
}

#endif
