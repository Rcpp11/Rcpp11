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

#ifndef Rcpp__protection_Shield_h
#define Rcpp__protection_Shield_h

namespace Rcpp{
    
    inline SEXP Rcpp_protect(SEXP x){
        if( x != R_NilValue ) PROTECT(x) ; 
        return x ; 
    }
    
    template <typename T>
    class Shield{
    public:
        Shield( SEXP t_) : t(Rcpp_protect(t_)){}
        ~Shield(){
            if( t != R_NilValue ) UNPROTECT(1) ;    
        }
        Shield( const Scoped& ) = delete ;
        Shield& operator=( const Scoped& ) = delete ;
        
        Shield( Scoped&& other ) : t(other.t) {
            other.t = R_NilValue ;
        }
        Shield& operator=( Scoped&& other ){
            t = other.t ;
            other.t = R_NilValue ;
            return *this ;
        }
        
        operator SEXP() const { return t; }
        SEXP t ;
    } ;
    
}

#endif
