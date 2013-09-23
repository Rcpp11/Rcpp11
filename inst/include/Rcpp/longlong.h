//
// longlong.h: Rcpp R/C++ interface class library -- long long support
//
// Copyright (C) 2013  Dirk Eddelbuettel and Romain Francois
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

#ifndef RCPP_LONG_LONG_H
#define RCPP_LONG_LONG_H

#if defined(RCPP_HAS_LONG_LONG_TYPES)

namespace Rcpp{
    namespace traits{

        template<> struct r_sexptype_traits<long long>{ enum{ rtype = REALSXP } ; } ;
        template<> struct r_sexptype_traits<unsigned long long>{ enum{ rtype = REALSXP } ; } ;
    
        template<> struct r_type_traits<long long>{ typedef r_type_primitive_tag r_category ; } ;
        template<> struct r_type_traits< std::pair<const std::string,long long> >{ typedef r_type_primitive_tag r_category ; } ;
        template<> struct r_type_traits<unsigned long long>{ typedef r_type_primitive_tag r_category ; } ;
        template<> struct r_type_traits< std::pair<const std::string,unsigned long long> >{ typedef r_type_primitive_tag r_category ; } ;
    
        template <> struct wrap_type_traits<long long> { typedef wrap_type_primitive_tag wrap_category; } ;
        template <> struct wrap_type_traits<unsigned long long> { typedef wrap_type_primitive_tag wrap_category; } ;
    }
}
#endif

#endif
