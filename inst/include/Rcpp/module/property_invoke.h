//
// Module_Property.h:  Rcpp modules
//
// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Module_property_invoke_h
#define Rcpp_Module_property_invoke_h

template <typename Class, typename Property, typename GetterType>
inline SEXP property_invoke_getter__impl( Property& prop, GetterType& getter, Class* object, std::true_type){
    return wrap( (object->*getter)() ) ;
}

template <typename Class, typename Property, typename GetterType>
inline SEXP property_invoke_getter__impl( Property& prop, GetterType& getter, Class* object, std::false_type){
    return wrap( (*getter)(object) ) ;
}

template <typename Class, typename Property, typename GetterType>
inline SEXP property_invoke_getter( Property& prop, GetterType& getter, Class* object){
    return property_invoke_getter__impl( prop, getter, object, typename std::is_member_function_pointer<GetterType>::type() );
}

#endif
