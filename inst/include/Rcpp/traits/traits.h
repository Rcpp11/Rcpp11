// traits.h:  traits to help wrap
//
// Copyright (C) 2012 - 2013 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__traits__traits__h
#define Rcpp__traits__traits__h

#include <Rcpp/traits/number_to_type.h>
#include <Rcpp/traits/is_wide_string.h>
#include <Rcpp/traits/char_type.h>
#include <Rcpp/traits/named_object.h>
#include <Rcpp/traits/has_na.h>
#include <Rcpp/traits/storage_type.h>
#include <Rcpp/traits/r_sexptype_traits.h>
#include <Rcpp/traits/storage_type.h>
#include <Rcpp/traits/comparator_type.h>
#include <Rcpp/traits/r_type_traits.h>
#include <Rcpp/traits/wrap_type_traits.h>
#include <Rcpp/traits/is_na.h>
#include <Rcpp/traits/is_finite.h>
#include <Rcpp/traits/is_infinite.h>
#include <Rcpp/traits/is_nan.h>
#include <Rcpp/traits/or_.h>
#include <Rcpp/traits/get_na.h>
#include <Rcpp/traits/is_trivial.h>
#include <Rcpp/traits/init_type.h>
#include <Rcpp/traits/both.h>
#include <Rcpp/traits/has_names.h>

#include <Rcpp/traits/remove_const_and_reference.h>
#include <Rcpp/traits/is_module_object.h>
#include <Rcpp/traits/is_primitive.h>
#include <Rcpp/traits/expands_to_logical_impl.h>
#include <Rcpp/traits/sfinae.h>
#include <Rcpp/traits/sequence.h>

#endif

