//
// Rcpp_init.cpp :  Initialize and register
//
// Copyright (C) 2010 - 2012 John Chambers, Dirk Eddelbuettel and Romain Francois
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
#include <R.h>
#include <Rinternals.h>
#include "internal.h"
#include <Rcpp/registration/registration.h>

using namespace Rcpp ;

#define DOT_EXT(name)  DotExternal(#name, &name)
#define DOT_CALL(name) DotCall(#name, &name)

// TODO: check that having this static does not mess up with 
//       RInside, and move it within init_Rcpp_routines otherwise
static R_CallMethodDef callEntries[]  = {
    DOT_CALL(Class__name),
    DOT_CALL(Class__has_default_constructor),
    DOT_CALL(CppClass__complete),
    DOT_CALL(CppClass__methods),
    DOT_CALL(CppObject__finalize),
    DOT_CALL(Module__classes_info),
    DOT_CALL(Module__complete),
    DOT_CALL(Module__get_class),
    DOT_CALL(Module__has_class),
    DOT_CALL(Module__has_function),
    DOT_CALL(Module__functions_arity),
    DOT_CALL(Module__functions_names),
    DOT_CALL(Module__name),
    DOT_CALL(Module__get_function),
    DOT_CALL(get_rcpp_cache),
    DOT_CALL(rcpp_error_recorder),
    DOT_CALL(as_character_externalptr),
    DOT_CALL(CppField__get),
    DOT_CALL(CppField__set),
    
    {NULL, NULL, 0}
}; 

static R_ExternalMethodDef extEntries[]  = {
    DOT_EXT(CppMethod__invoke),
    DOT_EXT(CppMethod__invoke_void),
    DOT_EXT(CppMethod__invoke_notvoid),
    DOT_EXT(InternalFunction_invoke),
    DOT_EXT(Module__invoke), 
    DOT_EXT(class__newInstance), 
    DOT_EXT(class__dummyInstance), 
    
    {NULL, NULL, 0}
} ;

// this is called by R_init_Rcpp11 that is in Module.cpp
extern "C" void init_Rcpp11_routines(DllInfo *info){
  /* Register routines, allocate resources. */
  R_registerRoutines(info, 
      NULL /* .C*/, 
      callEntries /*.Call*/,
      NULL /* .Fortran */,
      extEntries /*.External*/
  );
}
        
extern "C" void R_unload_Rcpp11(DllInfo *info) {
  /* Release resources. */
}
