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

#ifndef Rcpp_Module_MethodInvoker_h
#define Rcpp_Module_MethodInvoker_h
        
    template <typename Class, typename OUT, typename Method, typename... Args>
    class MethodInvoker {
    public: 
        typedef typename std::tuple< typename traits::input_parameter<Args>::type ...> Tuple ;
        
        MethodInvoker( Method method_, Class* object_, SEXP* args_ ) : 
            method(method_), object(object_), args(args_){}
        
        inline SEXP invoke( ){
            return invoke_dispatch( 
                typename std::is_member_function_pointer<Method>::type(), 
                typename traits::index_sequence<Args...>::type()
            ) ;
        }
        
        template <int... S>
        inline SEXP invoke_dispatch( std::true_type, traits::sequence<S...> ){
            return wrap( (object->*method)( get<S>() ... ) ) ;
        }
        template <int... S>
        inline SEXP invoke_dispatch( std::false_type, traits::sequence<S...> ){
            return wrap( method( object, get<S>() ... ) ) ;
        }
        
        
        template <int i>
        typename std::tuple_element<i, Tuple>::type get(){
            return typename std::tuple_element<i, Tuple>::type( args[i] ) ;   
        }
        
        Method method ;
        Class* object ;
        SEXP* args ;
    } ; 

    template <typename Class, typename Method, typename... Args >
    class MethodInvoker<Class,void,Method,Args...> {
    public: 
        typedef typename std::tuple< typename traits::input_parameter<Args>::type ...> Tuple ;
        
        MethodInvoker( Method method_, Class* object_, SEXP* args_ ) : 
            method(method_), object(object_), args(args_){}
        
        inline SEXP invoke( ){
            invoke_dispatch( 
                typename std::is_member_function_pointer<Method>::type(),
                typename traits::index_sequence<Args...>::type()
            ) ;
            return R_NilValue ;
        }
        
        template <int... S>
        inline void invoke_dispatch( std::true_type, traits::sequence<S...> ){
            (object->*method)( get<S>() ... ) ;
        }
        template <int... S>
        inline void invoke_dispatch( std::false_type, traits::sequence<S...> ){
            method( object, get<S>() ... ) ;
        }
        
        template <int i>
        typename std::tuple_element<i, Tuple>::type get(){
            return typename std::tuple_element<i, Tuple>::type( args[i] ) ;   
        }
        
        Method method ;
        Class* object ;
        SEXP* args ;
    } ; 

    

#endif
