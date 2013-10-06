//
// Evaluator.h:  protected evaluation
//
// Copyright (C) 2009 - 2012    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Evaluator_h
#define Rcpp_Evaluator_h

#define R_NO_REMAP
#include <Rinternals.h>

namespace Rcpp{ 

    SEXP Rcpp_evaluate(SEXP, SEXP) ;
    
    inline SEXP Rcpp_eval(SEXP expr, SEXP env){
        #if defined(COMPILING_RCPP11)
            return Rcpp_evaluate(expr, env) ;
        #else
            typedef decltype(Rcpp_eval) Fun ;
            static Fun eval = (Fun)R_GetCCallable("Rcpp11", "Rcpp_evaluate");
            return eval(expr, env) ;
        #endif
    }
    
    
    inline SEXP Rcpp_eval(SEXP expr){
        return Rcpp_eval( expr, R_GlobalEnv) ; 
    }
    
} // namespace Rcpp

#endif
