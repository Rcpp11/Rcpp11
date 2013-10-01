// Copyright (C) 2013    Romain Francois
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

#ifndef Rcpp__Dots__h
#define Rcpp__Dots__h

namespace Rcpp{

    class Dots {
    public:
        Dots( List data_, Environment env_): data(data_), env(env_){}
        
        SEXP eval( int i ){ return eval_(i); }
        
        template <typename T>
        T eval( int i ){
            return as<T>( eval_(i) ) ;
        }
        
        SEXP operator[]( int i ){ 
            return data[i] ;
        }
        
        inline size_t size() const{ return data.size(); } 
            
    private:
        
        inline SEXP eval_( int i){
            return Rf_eval( data[i], env ) ;
        }
        
        List data ;
        Environment env ;
    } ;

} // Rcpp 

#endif
