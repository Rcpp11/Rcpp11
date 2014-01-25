#ifndef Rcpp__R__h
#define Rcpp__R__h

// include R headers, but set R_NO_REMAP and access everything via Rf_ prefixes
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Complex.h>
#include <R_ext/Parse.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Callbacks.h>
#include <Rversion.h>

#endif
