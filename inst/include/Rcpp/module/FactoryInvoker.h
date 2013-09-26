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

#ifndef Rcpp_Module_FactoryInvoker_h
#define Rcpp_Module_FactoryInvoker_h
        
    template <typename Class, typename... Args>
    class FactoryInvoker {
    public:
        typedef Class* (*Fun)(Args...) ;
        typedef typename std::tuple< typename traits::input_parameter<Args>::type ...> Tuple ;
        
        FactoryInvoker( Fun factory_, SEXP* args_ ) : factory(factory_), args(args_){}
        
        inline Class* invoke( ){
            return invoke_dispatch( typename traits::index_sequence<Args...>::type() ) ;
        }
        
        template <int... S>
        inline Class* invoke_dispatch( traits::sequence<S...> ){
            return factory( get<S>() ... ) ;
        }
        
        template <int i>
        typename std::tuple_element<i, Tuple>::type get(){
            return typename std::tuple_element<i, Tuple>::type( args[i] ) ;   
        }
        
        Fun factory ;
        SEXP* args ;
    } ;
    
#endif
