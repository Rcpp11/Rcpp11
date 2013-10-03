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

#define DOTEXTERNAL(name) DotExternal(#name, &name) 
#define DOTCALL(name) DotCall(#name, &name )

// TODO: check that having this static does not mess up with 
//       RInside, and move it within init_Rcpp_routines otherwise
static R_CallMethodDef callEntries[]  = {
    DOTCALL(Class__name),
    DOTCALL(Class__has_default_constructor),
    DOTCALL(CppClass__complete),
    DOTCALL(CppClass__methods),
    DOTCALL(CppObject__finalize),
    DOTCALL(Module__classes_info),                             
    DOTCALL(Module__complete),
    DOTCALL(Module__get_class),
    DOTCALL(Module__has_class),
    DOTCALL(Module__has_function),
    DOTCALL(Module__functions_arity),
    DOTCALL(Module__functions_names),
    DOTCALL(Module__name),
    DOTCALL(Module__get_function),
    DOTCALL(get_rcpp_cache),
    DOTCALL(rcpp_error_recorder),
    DOTCALL(as_character_externalptr),
    DOTCALL(CppField__get),
    DOTCALL(CppField__set),
    
    {NULL, NULL, 0}
}; 

static R_ExternalMethodDef extEntries[]  = {
    DOTEXTERNAL(CppMethod__invoke),
    DOTEXTERNAL(CppMethod__invoke_void),
    DOTEXTERNAL(CppMethod__invoke_notvoid),
    DOTEXTERNAL(InternalFunction_invoke),
    DOTEXTERNAL(Module__invoke), 
    DOTEXTERNAL(class__newInstance), 
    DOTEXTERNAL(class__dummyInstance), 
    
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
