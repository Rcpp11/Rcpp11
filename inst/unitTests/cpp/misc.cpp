//
// misc.cpp:  misc unit tests
//
// Copyright (C) 2013    Dirk Eddelbuettel and Romain Francois
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
using namespace std;
#include <iostream>
#include <fstream>

// [[Rcpp::export]]
SEXP symbol_(){
    return LogicalVector::create( 
        Symbol( Rf_install("foobar") ) == Rf_install("foobar"), 
        Symbol( Rf_mkChar("foobar") ) == Rf_install("foobar"), 
        Symbol( Rf_mkString("foobar") ) == Rf_install("foobar"), 
        Symbol( "foobar" ) == Rf_install("foobar") 
    ) ;
}

// [[Rcpp::export]]
Symbol symbol_ctor(SEXP x){ return Symbol(x); }

// [[Rcpp::export]]
List Argument_(){
    Argument x("x"), y("y");
    return List::create( x = 2, y = 3 );
}

// [[Rcpp::export]] 
SEXP evaluator_error(){
    return Rcpp_eval( Rf_lang2( Rf_install("stop"), Rf_mkString( "boom" ) ) ) ;
}

// [[Rcpp::export]]
SEXP evaluator_ok(SEXP x){
    return Rcpp_eval( Rf_lang2( Rf_install("sample"), x ) ) ;
}

// [[Rcpp::export]]
void exceptions_(){
    throw std::range_error("boom") ;
}

// [[Rcpp::export]]
LogicalVector has_iterator_( ){
    return LogicalVector::create( 
        Rcpp::traits::has_iterator< std::vector<int> >::value, 
        Rcpp::traits::has_iterator< std::list<int> >::value, 
        Rcpp::traits::has_iterator< std::deque<int> >::value, 
        Rcpp::traits::has_iterator< std::set<int> >::value, 
        Rcpp::traits::has_iterator< std::map<std::string,int> >::value, 
        Rcpp::traits::has_iterator< std::pair<std::string,int> >::value, 
        Rcpp::traits::has_iterator< Rcpp::Symbol >::value 
   );
}

// [[Rcpp::export]]
LogicalVector na_proxy(){
    CharacterVector s = { "foo" } ;
    return LogicalVector::create( 
        NA_REAL    == NA, 
        NA_INTEGER == NA,
        NA_STRING  == NA,
        true       == NA, 
        false      == NA, 
        1.2        == NA, 
        12         == NA,
        "foo"      == NA,
        s[0]       == NA, 
        
        NA         == NA_REAL, 
        NA         == NA_INTEGER,
        NA         == NA_STRING,
        NA         == true, 
        NA         == false,
        NA         == 1.2  , 
        NA         == 12   ,
        NA         == "foo", 
        NA         == s[0]
        ) ;
}      

