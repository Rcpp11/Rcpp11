// sfinae.h:  
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

#ifndef Rcpp__traits__sfinae_h
#define Rcpp__traits__sfinae_h
  
namespace Rcpp {
namespace traits {
    struct __sfinae_types {
        typedef char __one;
        typedef struct { char __arr[2]; } __two;
    };

#define RCPP_HAS_TYPE_SFINAE(__NAME__,__TYPE__)                   \
template<typename T>                                              \
class __NAME__##__helper : __sfinae_types {                       \
    template<typename U> struct _Wrap_type { };                   \
    template<typename U>                                          \
        static __one __test(_Wrap_type<typename U::__TYPE__>*);   \
    template<typename U>                                          \
        static __two __test(...);                                 \
public:                                                           \
  static const bool value = sizeof(__test<T>(0)) == 1;            \
};                                                                \
template<typename T> struct __NAME__ :                            \
std::integral_constant<bool, __NAME__##__helper<T>::value >{ };   \


    RCPP_HAS_TYPE_SFINAE(expands_to_logical,r_expands_to_logical) 	
    RCPP_HAS_TYPE_SFINAE(has_iterator , iterator)
    RCPP_HAS_TYPE_SFINAE(is_generator , r_generator)
    RCPP_HAS_TYPE_SFINAE(is_exporter  , r_export_type)
    RCPP_HAS_TYPE_SFINAE(is_eigen_base,StorageKind)
    RCPP_HAS_TYPE_SFINAE(is_sugar_expression,rcpp_sugar_expression)
    RCPP_HAS_TYPE_SFINAE(matrix_interface, r_matrix_interface)
    
#undef RCPP_HAS_TYPE_SFINAE    
 
}}

#endif
