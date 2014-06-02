#ifndef Rcpp__sugar__operators__operators_h
#define Rcpp__sugar__operators__operators_h

#include <Rcpp/sugar/operators/r_binary_op.h>
#include <Rcpp/sugar/operators/r_arith_op.h>
#include <Rcpp/sugar/operators/unary_op_type.h>

// binary operators
#include <Rcpp/sugar/operators/logical_operators__Vector__Vector.h> 
#include <Rcpp/sugar/operators/logical_operators__Vector__primitive.h> 

// arith operators
#include <Rcpp/sugar/operators/arith_Vector_Vector.h>
#include <Rcpp/sugar/operators/arith_Vector_Primitive.h>
#include <Rcpp/sugar/operators/arith_Primitive_Vector.h>

// unary operators
#include <Rcpp/sugar/operators/Unary.h>

#endif
