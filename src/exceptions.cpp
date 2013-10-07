//
// exceptions.cpp: R/C++ interface class library -- exception handling
//
// Copyright (C) 2009 - 2012  Dirk Eddelbuettel and Romain Francois
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

#define COMPILING_RCPP11

#include <Rcpp.h>
#include "internal.h"

using Rcpp::Scoped ;

#define RCPP_SET_VECTOR_ELT SET_VECTOR_ELT 

namespace Rcpp{
    
    exception::exception(const char* message_) : message(message_) {}
    exception::exception( const char* message_, const char* file, int line) : message(message_){
	rcpp_set_stack_trace( stack_trace(file,line) ) ;
    }
    exception::~exception() throw(){}

#define RCPP_EXCEPTION_WHAT(__CLASS__)					\
    const char* __CLASS__::what() const throw(){ return message.c_str(); }

    RCPP_EXCEPTION_WHAT(exception)
    RCPP_EXCEPTION_WHAT(not_compatible)
    RCPP_EXCEPTION_WHAT(S4_creation_error)
    RCPP_EXCEPTION_WHAT(reference_creation_error)
    RCPP_EXCEPTION_WHAT(no_such_binding)
    RCPP_EXCEPTION_WHAT(binding_not_found)
    RCPP_EXCEPTION_WHAT(binding_is_locked)
    RCPP_EXCEPTION_WHAT(no_such_namespace)
    RCPP_EXCEPTION_WHAT(function_not_exported)
    RCPP_EXCEPTION_WHAT(eval_error)

#undef RCPP_EXCEPTION_WHAT

#define RCPP_SIMPLE_EXCEPTION_WHAT(__CLASS__,__MESSAGE__)		\
const char* __CLASS__::what() const throw(){ return __MESSAGE__ ; }

    RCPP_SIMPLE_EXCEPTION_WHAT(not_a_matrix, "not a matrix" )
    RCPP_SIMPLE_EXCEPTION_WHAT(index_out_of_bounds, "index out of bounds" )
    RCPP_SIMPLE_EXCEPTION_WHAT(parse_error, "parse error") 
    RCPP_SIMPLE_EXCEPTION_WHAT(not_s4, "not an S4 object" )
    RCPP_SIMPLE_EXCEPTION_WHAT(not_reference, "not a reference S4 object" )
    RCPP_SIMPLE_EXCEPTION_WHAT(not_initialized, "C++ object not initialized" )
    RCPP_SIMPLE_EXCEPTION_WHAT(no_such_slot, "no such slot" )
    RCPP_SIMPLE_EXCEPTION_WHAT(no_such_field, "no such field" )
    RCPP_SIMPLE_EXCEPTION_WHAT(not_a_closure, "not a closure" )
    RCPP_SIMPLE_EXCEPTION_WHAT(no_such_function, "no such function" )
    RCPP_SIMPLE_EXCEPTION_WHAT(unevaluated_promise, "promise not yet evaluated" )

#undef RCPP_SIMPLE_EXCEPTION_WHAT
}

