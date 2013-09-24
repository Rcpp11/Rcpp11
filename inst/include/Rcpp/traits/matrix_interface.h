// matrix_interface.h:  
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

#ifndef Rcpp__traits__matrix_interface_h
#define Rcpp__traits__matrix_interface_h

// helper trait to disambiguate things that want to be logical vectors
// from containers of int

namespace Rcpp{
namespace traits{

	template<typename T>
	class _has_matrix_interface_helper : __sfinae_types {
      template<typename U> struct _Wrap_type { };

      template<typename U>
        static __one __test(_Wrap_type<typename U::r_matrix_interface>*);

      template<typename U>
        static __two __test(...);

    public:
      static const bool value = sizeof(__test<T>(0)) == 1;
    };
  
  template<typename T> struct matrix_interface : 
  	std::integral_constant<bool, _has_matrix_interface_helper<T>::value >{ };
    
    
} 
}

#endif
