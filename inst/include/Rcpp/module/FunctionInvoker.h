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

#ifndef Rcpp_Module_FunctionInvoker_h
#define Rcpp_Module_FunctionInvoker_h

namespace Rcpp{
    
    template <typename OUT, typename... Args>
    class FunctionInvoker {
    public:
        typedef OUT (*Fun)(Args...) ;
        typedef typename std::tuple< typename traits::input_parameter<Args>::type ...> Tuple ;
        
        FunctionInvoker( Fun fun_, SEXP* args_ ) : fun(fun_), args(args_){}
        
        inline SEXP invoke( ){
            return invoke_dispatch( typename traits::index_sequence<Args...>::type() ) ;
        }
        
        template <int... S>
        inline SEXP invoke_dispatch( traits::sequence<S...> ){
            return wrap( fun( get<S>() ... ) ) ;
        }
        
        template <int i>
        typename std::tuple_element<i, Tuple>::type get(){
            return typename std::tuple_element<i, Tuple>::type( args[i] ) ;   
        }
        
        Fun fun ;
        SEXP* args ;
    } ;

    template <typename... Args>
    class FunctionInvoker<void,Args...> {
    public:
        typedef void (*Fun)(Args...) ;
        typedef typename std::tuple< typename traits::input_parameter<Args>::type ...> Tuple ;
        
        FunctionInvoker( Fun fun_, SEXP* args_ ) : fun(fun_), args(args_){}
        
        inline SEXP invoke( ){
            invoke_dispatch( typename traits::index_sequence<Args...>::type() ) ;
            return R_NilValue ;
        }
        
        template <int... S>
        inline void invoke_dispatch( traits::sequence<S...> ){
            fun( get<S>() ... ) ;
        }
        
        template <int i>
        typename std::tuple_element<i, Tuple>::type get(){
            return typename std::tuple_element<i, Tuple>::type( args[i] ) ;   
        }
        
        Fun fun ;
        SEXP* args ;
    } ;

}   
#endif
