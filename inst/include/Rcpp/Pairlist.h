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

#ifndef Rcpp_Pairlist_h
#define Rcpp_Pairlist_h

namespace Rcpp{

    class Pairlist : 
        RCPP_POLICIES(Pairlist), 
        public DottedPairProxyPolicy<Pairlist>, 
        public DottedPairImpl<Pairlist>
    {
    public:         
        RCPP_GENERATE_CTOR_ASSIGN(Pairlist) 
	
        Pairlist(SEXP x){
            set__( r_cast<LISTSXP>(x) ) ;    
        }
        
        template<typename... Args> 
        Pairlist( const Args&... args) {
            set__(pairlist(args...)) ;    
        }
       
        void update(SEXP){}
    } ;
        
}
#endif
