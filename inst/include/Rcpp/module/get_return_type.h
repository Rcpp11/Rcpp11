//
// Module_generated_get_return_type.h: 
//
// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Module_generated_get_return_type_h
#define Rcpp_Module_generated_get_return_type_h

struct void_type{} ;

template <typename OUT>
inline std::string get_return_type_dispatch( std::false_type ){
    return demangle( typeid(OUT).name() ).data() ;
}
template <typename OUT>
inline std::string get_return_type_dispatch( std::true_type ){
    typedef typename std::remove_pointer<OUT>::type pointer ;
    std::string res = demangle( typeid( pointer ).name() ).data() ;
    res += "*" ;
    return res ;
}

template <typename OUT>
inline std::string get_return_type(){
    return get_return_type_dispatch<OUT>( typename std::is_pointer<OUT>::type() ) ;
}
template <>
inline std::string get_return_type<void_type>(){
    return "void" ;
}
template <>
inline std::string get_return_type<SEXP>(){
    return "SEXP" ;
}
template <>
inline std::string get_return_type<Rcpp::IntegerVector>(){
    return "Rcpp::IntegerVector" ;
}
template <>
inline std::string get_return_type<Rcpp::NumericVector>(){
    return "Rcpp::NumericVector" ;
}
template <>
inline std::string get_return_type<Rcpp::RawVector>(){
    return "Rcpp::RawVector" ;
}
template <>
inline std::string get_return_type<Rcpp::ExpressionVector>(){
    return "Rcpp::ExpressionVector" ;
}
template <>
inline std::string get_return_type<Rcpp::List>(){
    return "Rcpp::List" ;
}
template <>
inline std::string get_return_type<Rcpp::CharacterVector>(){
    return "Rcpp::CharacterVector" ;
}

#endif
