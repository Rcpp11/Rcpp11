//
// RcppCommon.h:  common include and defines statements
//
// Copyright (C) 2008 - 2009 Dirk Eddelbuettel
// Copyright (C) 2009 - 2013 Dirk Eddelbuettel and Romain Francois
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

#ifndef RcppCommon_h
#define RcppCommon_h

// #define RCPP_DEBUG_LEVEL 1

#include <Rcpp/platform/compiler.h>
#include <Rcpp/macros/macros.h>

// include R headers, but set R_NO_REMAP and access everything via Rf_ prefixes
#define MAXELTSIZE 8192
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Complex.h>
#include <R_ext/Parse.h>
#include <R_ext/Rdynload.h>
#include <Rversion.h>
#include <Rcpp/Scoped.h>

#define RCPP_SET_VECTOR_ELT SET_VECTOR_ELT 
// #define RCPP_SET_VECTOR_ELT(v,i,x) { Rprintf("SET_VECTOR_ELT(%p, %d, %p). file = %s, line = %d\n", (SEXP)v, i, (SEXP)x, __FILE__, __LINE__) ; SET_VECTOR_ELT( (SEXP)v,i,(SEXP)x) ; } 

#ifdef __cplusplus
extern "C" 
#endif 
const char * sexp_to_name(int sexp_type);

#include <cstdint>
#include <array>
#include <type_traits>
#include <iterator>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>

#include <map>
#include <set>
#include <stdexcept>
#include <vector>
#include <deque>
#include <functional>
#include <numeric>
#include <algorithm>
#include <complex>
#include <limits>
#include <typeinfo>
#include <tuple>
#include <utility>

#include <Rcpp/complex.h>
#include <Rcpp/barrier.h>

#include <Rcpp/exceptions.h>
#include <Rcpp/Demangler.h>

namespace Rcpp{
    template <typename T> class object ;
    class String ;
    
    template <int RTYPE> class Vector ;
    template <int RTYPE> class Matrix ;
    using CharacterVector = Vector<STRSXP> ;
    using List = Vector<VECSXP> ; 
    using ExpressionVector = Vector<EXPRSXP> ; 
    
    template <typename CLASS> class RObjectStorage ;
    template < template <class> class StoragePolicy > class RObject_Impl ;
    using RObject = RObject_Impl<RObjectStorage> ;
   
    class Function ;
    class Language ;
    class DataFrame ;
    class Environment ;
    class Pairlist ;
    class Promise ;
    class Symbol ;
    class WeakReference ;
    class Reference ;
    class S4 ;
    class Formula ;
    namespace internal{
		template <typename Class> SEXP make_new_object( Class* ptr ) ;	
	}
}	
namespace Rcpp{
    SEXP Rcpp_PreserveObject(SEXP x) ;
    void Rcpp_ReleaseObject(SEXP x) ;
    SEXP Rcpp_ReplaceObject(SEXP x, SEXP y) ;
}

#include <Rcpp/traits/traits.h>
#include <Rcpp/Named.h>

#include <Rcpp/internal/caster.h>
#include <Rcpp/internal/r_vector.h>
#include <Rcpp/r_cast.h>

#include <Rcpp/api/bones/bones.h>

#include <Rcpp/internal/export.h>
#include <Rcpp/internal/r_coerce.h>
#include <Rcpp/as.h>
#include <Rcpp/InputParameter.h>
#include <Rcpp/is.h>

#include <Rcpp/vector/VectorBase.h>
#include <Rcpp/vector/MatrixBase.h>

#include <Rcpp/wrap/wrap.h>

#include <Rcpp/internal/Proxy_Iterator.h>
#include <Rcpp/internal/const_Proxy_Iterator.h>
#include <Rcpp/internal/converter.h>

#include <Rcpp/algo.h>

#include <Rcpp/sugar/sugar_forward.h>

#include <Rcpp/cache.h>

// "Rcout" iostream class contributed by Jelmer Ypma
#include <Rcpp/iostream/Rstreambuf.h>
#include <Rcpp/iostream/Rostream.h>

#include <Rcpp/longlong.h>

#endif
