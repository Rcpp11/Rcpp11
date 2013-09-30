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

#ifndef Rcpp__Vector_h
#define Rcpp__Vector_h

#include <Rcpp/vector/00_forward.h>

#include <Rcpp/vector/no_init.h>
#include <Rcpp/vector/vector_from_string.h>
#include <Rcpp/vector/eval_methods.h>

#include <Rcpp/vector/converter.h>
#include <Rcpp/vector/RangeIndexer.h>

#include <Rcpp/vector/Vector.h>

#include <Rcpp/vector/simple_name_proxy.h>
#include <Rcpp/vector/string_name_proxy.h>
#include <Rcpp/vector/generic_name_proxy.h>

#include <Rcpp/vector/simple_const_name_proxy.h>
#include <Rcpp/vector/string_const_name_proxy.h>
#include <Rcpp/vector/generic_const_name_proxy.h>

#include <Rcpp/vector/proxy.h>
#include <Rcpp/vector/traits.h>

#include <Rcpp/vector/Matrix.h>
#include <Rcpp/vector/SubMatrix.h>
#include <Rcpp/vector/MatrixRow.h>
#include <Rcpp/vector/MatrixColumn.h>

#include <Rcpp/vector/instantiation.h>
#include <Rcpp/vector/create.h>

#include <Rcpp/vector/string_proxy.h>
#include <Rcpp/vector/const_string_proxy.h>
#include <Rcpp/vector/generic_proxy.h>
#include <Rcpp/vector/const_generic_proxy.h>

#include <Rcpp/String.h>
#include <Rcpp/Na_Proxy.h>

#include <Rcpp/vector/LazyVector.h>
#include <Rcpp/vector/swap.h>
#include <Rcpp/vector/Demangler.h>

#endif 
