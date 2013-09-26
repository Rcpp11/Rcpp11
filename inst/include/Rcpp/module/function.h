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

#ifndef Rcpp_Module_function_h
#define Rcpp_Module_function_h

template <typename OUT, typename... Args>                                                                   
void function( const char* name_,  OUT (*fun)(Args...), const char* docstring = 0){
    Rcpp::Module* scope = ::getCurrentScope() ;
    if( scope ){
        scope->Add( name_, new CppFunction_Impl<OUT, Args...>( fun, docstring ) ) ;
    }
}

template <typename OUT, typename... Args>                                                                   
void function( const char* name_,  OUT (*fun)(Args...), Rcpp::List formals, const char* docstring = 0){
    Rcpp::Module* scope = ::getCurrentScope() ;
    if( scope ){
        scope->Add( name_, new CppFunction_WithFormals_Impl<OUT, Args...>( fun, formals, docstring ) ) ;
    }
}

template <typename OUT, typename... Args>                                                                   
void debug_function( const char* name_,  OUT (*fun)(Args...), const char* docstring = 0){
    Rcpp::Module* scope = ::getCurrentScope() ;
    if( scope ){
        scope->Add( name_, new Debug_CppFunction_Impl<OUT, Args...>( fun, name_, docstring ) ) ;
    }
}

template <typename OUT, typename... Args>                                                                   
void debug_function( const char* name_,  OUT (*fun)(Args...), Rcpp::List formals, const char* docstring = 0){
    Rcpp::Module* scope = ::getCurrentScope() ;
    if( scope ){
        scope->Add( name_, new Debug_CppFunction_WithFormals_Impl<OUT, Args...>( fun, name_, formals, docstring ) ) ;
    }
}


#endif
