//
// Rcpp.h: R/C++ interface class library
//
// Copyright (C) 2008 - 2009 Dirk Eddelbuettel
// Copyright (C) 2009 - 2012 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp11_h
#define Rcpp11_h

#if defined(Rcpp_hpp)
# error "Detecting Rcpp. It is probably a bad idea to compile against Rcpp11 and Rcpp together"
#endif

/* it is important that this comes first */
#include <RcppCommon.h>

#include <Rcpp/exceptions.h>

#include <Rcpp/RObject.h>

#include <Rcpp/Promise.h>
#include <Rcpp/S4.h>
#include <Rcpp/Reference.h>
#include <Rcpp/clone.h>
#include <Rcpp/grow.h>
#include <Rcpp/Dimension.h>
#include <Rcpp/Environment.h>
#include <Rcpp/Evaluator.h>

#include <Rcpp/Vector.h>
#include <Rcpp/sugar/nona/nona.h>
#include <Rcpp/Extractor.h>

#include <Rcpp/XPtr.h>
#include <Rcpp/Symbol.h>
#include <Rcpp/Language.h>
#include <Rcpp/DottedPair.h>
#include <Rcpp/Pairlist.h>
#include <Rcpp/Function.h>
#include <Rcpp/WeakReference.h>
#include <Rcpp/Formula.h>
#include <Rcpp/DataFrame.h>

#include <Rcpp/Module.h>

#include <Rmath.h>
#include <Rcpp/sugar/undoRmath.h>

#ifndef RCPP_NO_SUGAR
#include <Rcpp/sugar/sugar.h>
#include <Rcpp/stats/stats.h>
#endif

// wrappers for R API 'scalar' functions
#include <Rcpp/Rmath.h>

// this stays at the very end, because it needs to 
// 'see' all versions of wrap
#include <Rcpp/wrap/wrap_end.h>

#include <Rcpp/api/meat/meat.h>

#endif
