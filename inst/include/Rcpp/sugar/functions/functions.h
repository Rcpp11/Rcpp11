#ifndef RCPP_SUGAR_FUNCTIONS_H
#define RCPP_SUGAR_FUNCTIONS_H

/* for exp( double ) */
#include <cmath>

#include <Rcpp/sugar/functions/FunctionWithConversion.h>

#include <Rcpp/sugar/Range.h>
#include <Rcpp/sugar/functions/Lazy.h>

#include <Rcpp/sugar/functions/math.h>

#include <Rcpp/sugar/functions/complex.h>

#include <Rcpp/sugar/functions/is.h>

#include <Rcpp/sugar/functions/na_omit.h>
#include <Rcpp/sugar/functions/seq_along.h>
#include <Rcpp/sugar/functions/sapply.h>
#include <Rcpp/sugar/functions/mapply.h>
#include <Rcpp/sugar/functions/lapply.h>
#include <Rcpp/sugar/functions/ifelse.h>
#include <Rcpp/sugar/functions/pmin.h>
#include <Rcpp/sugar/functions/pmax.h>
#include <Rcpp/sugar/functions/clamp.h>
#include <Rcpp/sugar/functions/min.h>
#include <Rcpp/sugar/functions/max.h>
#include <Rcpp/sugar/functions/range.h>
#include <Rcpp/sugar/functions/sign.h>
#include <Rcpp/sugar/functions/diff.h>
#include <Rcpp/sugar/functions/pow.h>
#include <Rcpp/sugar/functions/rep.h>
#include <Rcpp/sugar/functions/rep_len.h>
#include <Rcpp/sugar/functions/rep_each.h>
#include <Rcpp/sugar/functions/rev.h>
#include <Rcpp/sugar/functions/head.h>
#include <Rcpp/sugar/functions/tail.h>
#include <Rcpp/sugar/functions/filter.h>
#include <Rcpp/sugar/functions/reduce.h>
#include <Rcpp/sugar/functions/sum.h>
#include <Rcpp/sugar/functions/mean.h>
#include <Rcpp/sugar/functions/var.h>
#include <Rcpp/sugar/functions/sd.h>
#include <Rcpp/sugar/functions/cumsum.h>
#include <Rcpp/sugar/functions/which_min.h>
#include <Rcpp/sugar/functions/which_max.h>

#include <Rcpp/sugar/functions/import.h>
#include <Rcpp/sugar/functions/transform.h>

#include <Rcpp/sugar/functions/unique.h>
#include <Rcpp/sugar/functions/match.h>
#include <Rcpp/sugar/functions/table.h>
#include <Rcpp/sugar/functions/duplicated.h>
#include <Rcpp/sugar/functions/setdiff.h>

#include <Rcpp/sugar/functions/strings/strings.h>
#include <Rcpp/sugar/functions/replicate.h>

#endif
