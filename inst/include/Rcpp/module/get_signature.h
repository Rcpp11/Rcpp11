//
// Module_get_signature.h: 
//
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

#ifndef Rcpp_Module_get_signature_h
#define Rcpp_Module_get_signature_h

namespace Rcpp{
    
    template <typename... Args>
    struct SignatureBody ;
    
    template <typename First, typename... Args>
    struct SignatureBody<First, Args...> {
        static void process( std::string& s ){
            s += get_return_type<First>() ;
            s += ", " ;
            SignatureBody<Args...>::process(s) ;
        }
    } ;
    
    template <typename First>
    struct SignatureBody<First>{
        static void process( std::string& s ){
            s += get_return_type<First>() ;
        }
    } ;
    
    template <>
    struct SignatureBody<>{
        static void process( std::string& ){}
    } ;
    
    template <typename OUT, typename... Args>
    inline void signature(std::string& s, const char* name ){
        s.clear() ;
        s += get_return_type<OUT>() ;
        s += " " ;
        s += name ;
        s += "(" ;
        SignatureBody<Args...>::process( s ) ;
        s += ")" ;
    }
    
    template <typename... Args>
    inline void ctor_signature( std::string& s, const std::string& classname ){
        s.assign(classname) ;
        s += "(" ; 
        SignatureBody<Args...>::process( s ) ;
        s += ")" ;
    }

}
#endif
