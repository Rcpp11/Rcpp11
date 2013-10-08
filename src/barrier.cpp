//
// barrier.cpp:  write barrier
//
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

#define COMPILING_RCPP11
#define USE_RINTERNALS
#include <Rinternals.h>
#include <Rcpp/barrier.h>
#include "internal.h"
#include <algorithm>
#include <Rcpp/macros/debug.h>

#define RCPP_SET_VECTOR_ELT SET_VECTOR_ELT 

SEXP get_string_elt__impl(SEXP x, int i){
    return STRING_ELT(x, i ) ;
}    
const char* char_get_string_elt__impl(SEXP x, int i){
    return CHAR(STRING_ELT(x, i )) ;
}    
void set_string_elt__impl(SEXP x, int i, SEXP value){
    STRING_ELT(x, i) = value ;
}
void char_set_string_elt__impl(SEXP x, int i, const char* value){
    STRING_ELT(x, i) = Rf_mkChar(value) ; 
}
SEXP* get_string_ptr__impl(SEXP x){ return STRING_PTR(x) ; }

SEXP get_vector_elt__impl(SEXP x, int i){
    return VECTOR_ELT(x, i ) ;
}
void set_vector_elt__impl(SEXP x, int i, SEXP value){
    RCPP_SET_VECTOR_ELT(x, i, value ) ;
}
SEXP* get_vector_ptr__impl(SEXP x){ return VECTOR_PTR(x) ; }
void* dataptr__impl(SEXP x){ return DATAPTR(x); }

// when we already know x is a CHARSXP
const char* char_nocheck__impl( SEXP x ){ return CHAR(x); }

static bool Rcpp_cache_know = false ;
static SEXP Rcpp_cache = R_NilValue ;
static SEXP Rcpp_protection_stack = R_NilValue ;

#define RCPP_HASH_CACHE_INDEX 4
#define RCPP_PROTECTION_STACK_INDEX 5
#define RCPP_CACHE_SIZE 6

#ifndef RCPP_PROTECT_STACK_INITIAL_SIZE
#define RCPP_PROTECT_STACK_INITIAL_SIZE 16384
#endif

#ifndef RCPP_PROTECT_STACK_INCREMENT
#define RCPP_PROTECT_STACK_INCREMENT 4096
#endif

#ifndef RCPP_HASH_CACHE_INITIAL_SIZE
#define RCPP_HASH_CACHE_INITIAL_SIZE 1024
#endif 

// only used for debugging
SEXP get_rcpp_cache() {
    RCPP_DEBUG( "get_rcpp_cache (known = %s)", (Rcpp_cache_know ? "true" : "false" ) )
    if( ! Rcpp_cache_know ){
        SEXP getNamespaceSym = Rf_install("getNamespace"); 
        SEXP RCPP       = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
        Rcpp_cache      = Rf_findVarInFrame( RCPP, Rf_install(".rcpp_cache") ) ;
        Rcpp_cache_know = true ;
        Rcpp_protection_stack = VECTOR_ELT(Rcpp_cache, RCPP_PROTECTION_STACK_INDEX) ;
        UNPROTECT(1) ;
    }
    RCPP_DEBUG( "  [get_rcpp_cache] Rcpp_cache = <%p>", Rcpp_cache )
        
    return Rcpp_cache ;
}

namespace Rcpp {
    	SEXP get_Rcpp11_namespace__impl(){ 
    	    return VECTOR_ELT( get_rcpp_cache() , 0 ) ;
	}
	
}

static void set_error_occured(SEXP cache, bool occured){
    RCPP_DEBUG( "set_error_occured( <%p>, %s, %s )", cache, PRETTY_BOOL(occured), PRETTY_BOOL(cache==R_NilValue) )
    RCPP_DEBUG( "R_NilValue = <%p>", R_NilValue )
    RCPP_SET_VECTOR_ELT( cache, 1, Rf_ScalarLogical(occured) ) ;
}

void set_current_error(SEXP cache, SEXP e){ 
    RCPP_DEBUG( "set_current_error( <%p>, <%p> )", cache, e ) ;
    RCPP_SET_VECTOR_ELT( cache, 2, e ) ;
}

SEXP rcpp_set_stack_trace(SEXP e){
    RCPP_SET_VECTOR_ELT( get_rcpp_cache(), 3, e ) ;
    return R_NilValue ;
}

SEXP rcpp_get_stack_trace(){
    return VECTOR_ELT( get_rcpp_cache(), 3 ) ;
}

SEXP init_Rcpp11_cache(){ 
    RCPP_DEBUG( "init_Rcpp11_cache()\n" )
	
    SEXP getNamespaceSym = Rf_install("getNamespace"); 
    SEXP RCPP    = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
    SEXP cache   = PROTECT( Rf_allocVector( VECSXP, RCPP_CACHE_SIZE ) ) ;
    
    // the Rcpp namespace
	RCPP_SET_VECTOR_ELT( cache, 0, RCPP ) ;
	set_error_occured( cache, false ) ;
	set_current_error( cache, R_NilValue ) ;
	RCPP_SET_VECTOR_ELT( cache, 3, R_NilValue ) ; // stack trace
	RCPP_SET_VECTOR_ELT( cache, RCPP_HASH_CACHE_INDEX, Rf_allocVector(INTSXP, RCPP_HASH_CACHE_INITIAL_SIZE) ) ;
	SEXP stack = PROTECT( Rf_allocVector(VECSXP, RCPP_PROTECT_STACK_INITIAL_SIZE) ) ;
	// we use true length to store "top"
	SET_TRUELENGTH(stack, -1 ) ;
	RCPP_SET_VECTOR_ELT( cache, RCPP_PROTECTION_STACK_INDEX, stack ) ;
	Rf_defineVar( Rf_install(".rcpp_cache"), cache, RCPP );
    
	UNPROTECT(3) ;
	return cache ;
}

SEXP reset_current_error(){
    RCPP_DEBUG("reset_current_error")
    SEXP cache = get_rcpp_cache() ;
    
    // error occured
    set_error_occured( cache, false ) ;
	
    // current error
    set_current_error( cache, R_NilValue ) ;
	
    // stack trace
    RCPP_SET_VECTOR_ELT( cache, 3, R_NilValue ) ;
	
    return R_NilValue ;
}

int error_occured(){
    SEXP err = VECTOR_ELT( get_rcpp_cache(), 1 ) ;
    return LOGICAL(err)[0] ;
}

SEXP rcpp_error_recorder(SEXP e){ 
    SEXP cache = get_rcpp_cache() ;
    
    // error occured
    
    RCPP_DEBUG( "rcpp_error_recorder()\n" )
	set_error_occured( cache, true ) ;
	
    // current error
    set_current_error(cache, e ) ;
    
    return R_NilValue ;
}

SEXP rcpp_get_current_error(){
    return VECTOR_ELT( get_rcpp_cache(), 2 ) ;
}

namespace Rcpp{
    
    int* get_cache__impl( int m){
        SEXP cache = get_rcpp_cache() ;
        SEXP hash_cache = VECTOR_ELT( cache, RCPP_HASH_CACHE_INDEX) ;
        int n = Rf_length(hash_cache) ;
        if( m > n ){
            SEXP hash_cache_ = PROTECT(Rf_allocVector( INTSXP, m)) ;
            RCPP_SET_VECTOR_ELT(cache,RCPP_HASH_CACHE_INDEX, hash_cache_); 
            hash_cache = hash_cache_ ;
        }
        int *res = INTEGER(hash_cache) ;
        std::fill(res, res+m, 0 ) ;
        return res ;
    }

}
