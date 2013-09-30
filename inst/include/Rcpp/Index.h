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

#ifndef Rcpp__Index__h
#define Rcpp__Index__h

namespace Rcpp{
    
    template <int N, typename... Args>
    constexpr bool ValidIndexArgs() {
        return traits::and_<std::is_convertible<Args, size_t>...>::value && (N == sizeof...(Args) ) ;   
    }
    
    template <int N>
    class Index {
    public:
    
        template <
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type 
        >
        Index( Args... args ) : dimensions({ static_cast<size_t>(args)... }) {}
    
        template < 
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type
        >
        size_t operator()( Args... args){
            return get_index( args... ) ;    
        }
    
        inline size_t prod(){
            return std::accumulate( begin(dimensions), end(dimensions), 1, std::multiplies<double>() ) ;     
        }
        inline size_t size(){ 
            return N ;
        }
        
        inline operator SEXP() const { return wrap( dimensions ); }
        inline operator SEXP() { return wrap( dimensions ); }
        
    private:
        
        template <typename... Args >
        size_t get_index( size_t first, Args... args){
            return first + dimensions[ N - sizeof...(Args) - 1 ] * get_index( args... );
        }
        
        size_t get_index( size_t first ){
            return first ;
        }
        
        std::array<size_t,N> dimensions ;
        
    } ;
     
    
} // Rcpp 

#endif
