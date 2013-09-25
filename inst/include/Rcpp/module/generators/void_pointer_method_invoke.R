file <- file( "generated_void_pointer_method_invoke.h", open = "w" )
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

#ifndef Rcpp_Module_generated_void_pointer_method_invoke_h
#define Rcpp_Module_generated_void_pointer_method_invoke_h
     
    template <typename Class, typename OUT>
    void void_pointer_method_invoke( traits::number_to_type<0>, OUT (*Method)(Class*), Class* object, SEXP* args ){ 
        Method(object) ;
    }
', file )

tmpl <- function(n) {
    sprintf( '
    template <typename Class, typename OUT, %s>
    void void_pointer_method_invoke( traits::number_to_type<%d>, OUT (*Method)(Class*, %s), Class* object, SEXP* args ){ 
        %s
        Method( object, %s ) ;
    }
    ', 
    paste( sprintf("typename U%d", 1:n), collapse = ", " ),
    n, 
    paste( sprintf("U%d", 1:n), collapse = ", " ), 
    paste( sprintf("typename Rcpp::traits::input_parameter<U%d>::type x%d( args[%d] ) ;", 1:n, 1:n, 1:n), collapse = "\n        " ), 
    paste( sprintf("x%d", 1:n), collapse = ", " )
    )
}

writeLines( paste( sapply( 1:65, tmpl ), collapse = "\n" ), file )
writeLines( "\n#endif", file )
close( file )

