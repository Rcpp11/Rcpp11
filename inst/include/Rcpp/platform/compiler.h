//
// compiler.h:  check compiler
//
// Copyright (C) 2012 - 2013  Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__platform__compiler_h
#define Rcpp__platform__compiler_h

// only supporting gcc and clang for now
#undef GOOD_COMPILER_FOR_RCPP
#if defined(__GNUC__) || defined(__clang__)
    #define GOOD_COMPILER_FOR_RCPP
#endif

#ifndef GOOD_COMPILER_FOR_RCPP
    # error "This compiler is not supported, only gcc and clang are supported"
#endif

#include <initializer_list>
#include <unordered_map>
#include <unordered_set>


#endif
