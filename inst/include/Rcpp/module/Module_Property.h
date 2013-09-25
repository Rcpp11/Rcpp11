//
// Module_Property.h:  Rcpp modules
//
// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Module_Property_h
#define Rcpp_Module_Property_h

template <typename Class, typename PROP, typename GetterType, typename SetterType, bool debug>
class CppProperty_Read_Write : public CppProperty<Class> {
public:         
    typedef CppProperty<Class> prop_class ;
    typedef typename std::integral_constant<bool, debug> debug_type ;

    CppProperty_Read_Write( GetterType getter_, SetterType setter_, const char* prop_name_, const char* doc = 0 ) : 
        prop_class(doc), getter(getter_), setter( setter_), prop_name(prop_name_) {}
                
    SEXP get(Class* object     ) { return property_invoke_getter<Class,PROP,CppProperty_Read_Write,GetterType>(*this, getter, object, prop_name, debug_type() ) ; }
    void set(Class* object, SEXP value) { property_invoke_setter<Class,PROP,CppProperty_Read_Write,SetterType>(*this, setter, object, value, prop_name, debug_type() ) ; }                
    bool is_readonly(){ return false ; }
    std::string get_class(){ return DEMANGLE(PROP); }
                        
private:
    GetterType getter ;
    SetterType setter ;
    std::string class_name ;
    std::string prop_name ;
                                
} ;

#endif
