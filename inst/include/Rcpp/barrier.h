//
// barrier.h:  crossin the write barrier
//
// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__barrier__h
#define Rcpp__barrier__h

#include <Rcpp/macros/macros.h>

SEXP get_string_elt__impl(SEXP, int) ;
inline SEXP get_string_elt(SEXP s, int i){
    GET_CALLABLE(get_string_elt__impl, s, i)
}

const char* char_get_string_elt__impl(SEXP, int) ;
inline const char* char_get_string_elt(SEXP s, int i){
    GET_CALLABLE(char_get_string_elt__impl, s, i)
}

void set_string_elt__impl(SEXP, int, SEXP) ;
inline void set_string_elt(SEXP s, int i, SEXP v){
    GET_CALLABLE(set_string_elt__impl, s, i, v)
}

void char_set_string_elt__impl(SEXP, int, const char*) ;        
inline void char_set_string_elt(SEXP s, int i, const char* v){
    GET_CALLABLE(char_set_string_elt__impl, s, i, v )    
}

SEXP* get_string_ptr__impl(SEXP) ;
inline SEXP* get_string_ptr(SEXP s){
    GET_CALLABLE(get_string_ptr__impl, s)    
}

SEXP get_vector_elt__impl(SEXP, int) ;
inline SEXP get_vector_elt(SEXP v, int i){
    GET_CALLABLE(get_vector_elt, v, i)
}

void set_vector_elt__impl(SEXP, int, SEXP ) ;
inline void set_vector_elt(SEXP v, int i, SEXP x){
    GET_CALLABLE(set_vector_elt__impl, v, i, x)
}

SEXP* get_vector_ptr__impl(SEXP) ;
inline SEXP* get_vector_ptr(SEXP v){
    GET_CALLABLE(get_vector_ptr__impl, v)    
}

const char* char_nocheck__impl( SEXP ) ;
inline const char* char_nocheck( SEXP x){
    GET_CALLABLE(char_nocheck__impl, x)
}

void* dataptr__impl(SEXP) ;
inline void* dataptr(SEXP x){
    GET_CALLABLE(dataptr__impl, x) 
}

#endif
