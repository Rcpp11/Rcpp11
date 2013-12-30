//
// na.h - efficient NA testing
//
// Copyright (C) 2013 Kevin Ushey and Romain Francois
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

#ifndef Rcpp__internal__na__h
#define Rcpp__internal__na__h

namespace Rcpp {
namespace internal {

template <typename T>
bool Rcpp_IsNA(T x);

template <>
inline bool Rcpp_IsNA<double>(double x) {
  return memcmp(
    (char*) (&x),
    (char*) (&NA_REAL),
    sizeof(double)
  ) == 0;
}

template <typename T>
bool Rcpp_IsNaN(T x);

template <>
inline bool Rcpp_IsNaN<double>(double x) {
  return memcmp(
    (char*) (&x),
    (char*) (&R_NaN),
    sizeof(double)
  ) == 0;
}

}
}

#endif
