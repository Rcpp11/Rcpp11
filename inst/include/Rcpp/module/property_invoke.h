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

template <typename Class, typename PROP, typename Property, typename GetterType>
inline SEXP property_invoke_getter( Property& prop, GetterType& getter, Class* object, std::string& /* prop_name */, std::false_type /* debug = false */ ){
    return property_invoke_getter__impl<Class,Property,GetterType>( prop, getter, object, typename std::is_member_function_pointer<GetterType>::type() );
}
template <typename Class, typename PROP, typename Property, typename GetterType>
inline SEXP property_invoke_getter( Property& prop, GetterType& getter, Class* object, std::string& prop_name , std::true_type /* debug = false */ ){
    std::string log( "   " ) ;
    log += DEMANGLE(PROP) ;
    log += " ::" ;
    log += DEMANGLE(Class) ;
    log += " " ;
    log += prop_name ;
    Rprintf( "    %s ...", log.c_str() ) ;
    SEXP res = property_invoke_getter__impl<Class,Property,GetterType>( prop, getter, object, typename std::is_member_function_pointer<GetterType>::type() );
    Rprintf( "\n" );
    return res ;
}


template <typename Class, typename PROP, typename Property, typename SetterType>
inline void property_invoke_setter__impl( Property& prop, SetterType& setter, Class* object, SEXP value, std::true_type){
    typename traits::input_parameter<PROP>::type x(value) ; 
    (object->*setter)(x) ;
}
template <typename Class, typename PROP, typename Property, typename SetterType>
inline void property_invoke_setter__impl__isnull( Property& prop, SetterType& setter, Class* object, SEXP value, std::false_type){
    typename traits::input_parameter<PROP>::type x(value) ; 
    (*setter)(object, x) ;
}
template <typename Class, typename PROP, typename Property, typename SetterType>
inline void property_invoke_setter__impl__isnull( Property& prop, SetterType& setter, Class* object, SEXP value, std::true_type){
    throw std::range_error("property is read only") ;
}
template <typename Class, typename PROP, typename Property, typename SetterType>
inline void property_invoke_setter__impl( Property& prop, SetterType& setter, Class* object, SEXP value, std::false_type){
    property_invoke_setter__impl__isnull<Class,PROP,Property,SetterType>( prop, setter, object, value, typename std::is_same<SetterType, decltype(nullptr)>::type() ) ;
}

template <typename Class, typename PROP, typename Property, typename SetterType>
inline void property_invoke_setter( Property& prop, SetterType& setter, Class* object, SEXP value, std::string& /* prop_name */, std::false_type /* debug = false */ ){
    property_invoke_setter__impl<Class,PROP,Property,SetterType>( prop, setter, object, value, typename std::is_member_function_pointer<SetterType>::type() );
    
}

template <typename Class, typename PROP, typename Property, typename SetterType>
inline void property_invoke_setter( Property& prop, SetterType& setter, Class* object, SEXP value, std::string& prop_name, std::true_type /* debug = true */ ){
    std::string log( "   " ) ;
    log += DEMANGLE(PROP) ;
    log += " ::" ;
    log += DEMANGLE(Class) ;
    log += " " ;
    log += prop_name ;
    Rprintf( "    %s ...", log.c_str() ) ;
    property_invoke_setter__impl<Class,PROP,Property,SetterType>( prop, setter, object, value, typename std::is_member_function_pointer<SetterType>::type() );
    Rprintf( "\n" ) ;
}


#endif
