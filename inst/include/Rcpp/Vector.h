#ifndef Rcpp__Vector_h
#define Rcpp__Vector_h

#include <Rcpp/vector/00_forward.h>

#include <Rcpp/vector/no_init.h>
#include <Rcpp/vector/vector_from_string.h>
#include <Rcpp/vector/eval_methods.h>

#include <Rcpp/vector/converter.h>

#include <Rcpp/vector/Vector.h>

#include <Rcpp/vector/simple_name_proxy.h>
#include <Rcpp/vector/string_name_proxy.h>
#include <Rcpp/vector/generic_name_proxy.h>

#include <Rcpp/vector/simple_const_name_proxy.h>
#include <Rcpp/vector/string_const_name_proxy.h>
#include <Rcpp/vector/generic_const_name_proxy.h>

#include <Rcpp/vector/proxy.h>
#include <Rcpp/vector/traits.h>

#include <Rcpp/vector/Matrix.h>
#include <Rcpp/vector/SubMatrix.h>
#include <Rcpp/vector/MatrixRow.h>
#include <Rcpp/vector/MatrixColumn.h>

#include <Rcpp/vector/instantiation.h>
#include <Rcpp/vector/create.h>

#include <Rcpp/vector/string_proxy.h>
#include <Rcpp/vector/const_string_proxy.h>
#include <Rcpp/vector/generic_proxy.h>
#include <Rcpp/vector/const_generic_proxy.h>

#include <Rcpp/String.h>
#include <Rcpp/NA_Proxy.h>

#include <Rcpp/vector/concat_free.h>

#include <Rcpp/vector/LazyVector.h>
#include <Rcpp/vector/swap.h>
#include <Rcpp/vector/Demangler.h>

#endif
