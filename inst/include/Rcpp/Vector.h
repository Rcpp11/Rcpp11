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

#include <RcppCommon.h>
#include <Rcpp/Evaluator.h>
#include <Rcpp/exceptions.h>
#include <Rcpp/RObject.h>
#include <Rcpp/r_cast.h>

namespace Rcpp{
    namespace traits{
         template <int RTYPE, bool NA, typename VECTOR> struct Extractor ;  
    }
}

namespace Rcpp{

#include <Rcpp/vector/00_forward_Vector.h>
}
#include <Rcpp/vector/no_init.h>
namespace Rcpp{
#include <Rcpp/vector/00_forward_proxy.h>
#include <Rcpp/vector/00_forward_eval_methods.h>

#include <Rcpp/vector/converter.h>

template <int RTYPE> class MatrixRow ;
template <int RTYPE> class MatrixColumn ;
template <int RTYPE> class SubMatrix ;

#include <Rcpp/vector/RangeIndexer.h>

#include <Rcpp/vector/Vector.h>

#include <Rcpp/vector/proxy.h>
#include <Rcpp/vector/traits.h>

#include <Rcpp/vector/Matrix.h>
#include <Rcpp/vector/SubMatrix.h>
#include <Rcpp/vector/MatrixRow.h>
#include <Rcpp/vector/MatrixColumn.h>

#include <Rcpp/vector/instantiation.h>
}

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
