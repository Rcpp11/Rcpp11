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

#ifndef Rcpp__traits__sequence__h
#define Rcpp__traits__sequence__h
   
namespace Rcpp{
    namespace traits{
        
        template<int ...>
        struct sequence {};
        
        template<int N, int ...S> 
        struct gens : gens<N-1, N-1, S...> {};
        
        template<int ...S> 
        struct gens<0, S...>{ 
            typedef sequence<S...> type; 
        };
        
        template<typename... Args>
        struct index_sequence {
            typedef typename gens<sizeof...(Args)>::type type ;
        } ;
    }
}
#endif
