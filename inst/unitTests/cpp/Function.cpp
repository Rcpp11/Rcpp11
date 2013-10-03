//
// Function.cpp:  Rcpp::Function unit tests
//
// Copyright (C) 2013 Dirk Eddelbuettel and Romain Francois
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

#include <Rcpp.h>
using namespace Rcpp ;

// [[Rcpp::export]]
Function function_(SEXP x){ return Function(x) ; }

// [[Rcpp::export]]
NumericVector function_variadic(Function sort, NumericVector y){
    return sort( y, Named("decreasing", true) ) ;
}

// [[Rcpp::export]]
Environment function_env(Function fun){
    return fun.environment() ;
}

// [[Rcpp::export]]
Function function_namespace_env(){
    Environment ns = Environment::namespace_env( "stats" ) ;
    Function fun = ns[".asSparse"] ;  // accesses a non-exported function
    return fun;
}

