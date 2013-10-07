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

#ifndef RCPP_ROUTINE_H
#define RCPP_ROUTINE_H

namespace Rcpp {

    SEXP Rcpp_eval__impl(SEXP, SEXP) ;
    inline SEXP Rcpp_eval(SEXP expr, SEXP env){
        GET_CALLABLE(Rcpp_eval__impl,expr,env)
    }
    inline SEXP Rcpp_eval(SEXP expr){
        GET_CALLABLE(Rcpp_eval__impl,expr,R_GlobalEnv) 
    }
    
    const char * type2name__impl(int sexp_type);
    inline const char* type2name(int sexp_type){
        GET_CALLABLE(type2name__impl, sexp_type)    
    }
}
    
#endif
