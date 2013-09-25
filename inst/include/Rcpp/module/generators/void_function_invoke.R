file <- file( "generated_void_function_invoke.h", open = "w" )
writeLines('
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

#ifndef Rcpp_Module_generated_void_function_invoke_h
#define Rcpp_Module_generated_void_function_invoke_h
     
    inline void void_function_invoke( traits::number_to_type<0>, void (*ptr_fun)(void), SEXP* args ){ 
        ptr_fun() ;
    }
', file )

tmpl <- function(n) {
    indices <- seq(0,n-1)
    sprintf( '
    template <%s>
    void void_function_invoke( traits::number_to_type<%d>, void (*ptr_fun)(%s), SEXP* args ){ 
        %s
        ptr_fun(%s) ;
    }
    ', 
    paste( sprintf("typename U%d", indices), collapse = ", " ), 
    n,
    paste( sprintf("U%d", indices), collapse = ", " ), 
    paste( sprintf("typename Rcpp::traits::input_parameter<U%d>::type x%d( args[%d] ) ;", indices, indices, indices), collapse = "\n        " ), 
    paste( sprintf("x%d", indices), collapse = ", " )
    )
}

writeLines( paste( sapply( 1:65, tmpl ), collapse = "\n" ), file )
writeLines( "\n#endif", file )
close( file )

