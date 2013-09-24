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

#ifndef Rcpp_Module_Constructor_h
#define Rcpp_Module_Constructor_h

template <typename Class>
class Constructor_Base {
public:
    virtual Class* get_new( SEXP* args, int nargs ) = 0 ;
    virtual int nargs() = 0 ;
    virtual void signature(std::string& s, const std::string& class_name) = 0 ;
} ;

template <typename Class, typename... Args>
class Constructor_Impl : public Constructor_Base<Class>{
public:
    virtual Class* get_new( SEXP* args, int nargs ){
        return make_new<Class,Args...>( args, nargs ) ;
    }
    virtual int nargs(){ return sizeof...(Args) ; }
    virtual void signature(std::string& s, const std::string& class_name ){
        ctor_signature<Args...>(s, class_name) ;
    }
} ;

#endif
