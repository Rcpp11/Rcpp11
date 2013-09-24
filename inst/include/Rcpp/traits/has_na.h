// has_na.h:  NA handling
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
   
#ifndef Rcpp__traits__has_na__h
#define Rcpp__traits__has_na__h

namespace Rcpp{
namespace traits{

/**
 * Indentifies if a given SEXP type has the concept of missing values
 * 
 * This is false by default and specialized for all types that do 
 * have the concept
 */
template<int RTYPE> struct has_na : public std::false_type{} ;

/**
 * integer vectors support missing values
 */
template<> struct has_na<INTSXP> : public std::true_type{};

/**
 * numeric vectors support missing values
 */
template<> struct has_na<REALSXP> : public std::true_type{};

/**
 * complex vectors support missing values
 */
template<> struct has_na<CPLXSXP> : public std::true_type{};

/**
 * character vector support missing values
 */
template<> struct has_na<STRSXP> : public std::true_type{};

/**
 * logical vectors support missing values
 */
template<> struct has_na<LGLSXP> : public std::true_type{};

}
}

#endif
