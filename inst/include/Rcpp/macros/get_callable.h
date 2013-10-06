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

#ifndef Rcpp_macros_get_callable_h
#define Rcpp_macros_get_callable_h

#if defined(COMPILING_RCPP11)
#define GET_CALLABLE(__FUN__, ...) return __FUN__( __VA_ARGS__ ) ;
#else
#define GET_CALLABLE(__FUN__, ...)                          \
typedef decltype(__FUN__)* Fun ;                            \
static Fun fun = (Fun)R_GetCCallable( "Rcpp11", #__FUN__) ; \
return fun(__VA_ARGS__) ;
#endif

#endif
