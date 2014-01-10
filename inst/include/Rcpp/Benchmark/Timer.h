//
// Timer.h:  Rcpp benchmark utility
//
// Copyright (C) 2012 JJ Allaire, Dirk Eddelbuettel and Romain Francois
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

#ifndef RCPP_BENCHMARH_TIMER_H
#define RCPP_BENCHMARH_TIMER_H

#include <stdint.h>
#include <vector>
#include <string>

#define R_NO_REMAP
#include <Rinternals.h>

namespace Rcpp{

    nanotime_t get_nanotime(void); 
    
    namespace internal{
        String get_first( const std::pair<std::string,nanotime_t>& pair ){
            return pair.first ;    
        }
        double get_second( const std::pair<std::string,nanotime_t>& pair ){
            return static_cast<double>(pair.second) ;    
        }
    }
            
    class Timer {
    public:
        Timer() : data(), start_time( get_nanotime() ){}
        
        void step( const std::string& name ){
            nanotime_t now = get_nanotime() ;
            data.push_back( std::make_pair( name, now - start_time ) ) ;
            start_time = get_nanotime() ; 
        }
        
        operator SEXP() const {
            NumericVector out = transform( data.begin(), data.end(), internal::get_second ) ; 
            CharacterVector names = transform( data.begin(), data.end(), internal::get_first ) ;
            out.attr( "names" ) = names ;
            return out ;
        }
        
        private:
            typedef std::pair<std::string,nanotime_t> Step;
            typedef std::vector<Step> Steps;
            
            Steps data ;
            nanotime_t start_time ;
            
    } ;
    
}
    
#endif

