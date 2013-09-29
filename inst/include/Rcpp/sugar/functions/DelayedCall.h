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

#ifndef Rcpp__sugar__DelayedCall_h
#define Rcpp__sugar__DelayedCall_h

namespace Rcpp{
namespace sugar{

    template <typename OUT, typename FunctionType, typename... Args >
    class DelayedCall {
    public:
        typedef typename std::tuple<Args...> Tuple ;
        
        DelayedCall( FunctionType fun_, const Args&... args ): fun(fun_), data( args... ){}
        
        inline OUT operator()() const {
            return eval() ;
        }
        
        inline OUT eval() const {
            return invoke_dispatch( typename Rcpp::traits::index_sequence<Args...>::type() ) ;
        }
        
        template <int... S>
        inline OUT invoke_dispatch( Rcpp::traits::sequence<S...> ) const {
            return fun( std::get<S>(data) ... ) ;
        }
        
    private:
        size_t n ;
        FunctionType fun ;
        Tuple data ; 
    } ;


} // sugar

template <typename OUT, typename... Args>
inline auto call( OUT (*fun)(Args...), Args... args ) -> sugar::DelayedCall<OUT,decltype(fun), Args...>{
    return sugar::DelayedCall<OUT,decltype(fun), Args...>( fun, args...) ;    
}


} // Rcpp
#endif

