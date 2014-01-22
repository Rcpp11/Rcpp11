#ifndef Rcpp__vector_concat_free_h
#define Rcpp__vector_concat_free_h

namespace Rcpp {

namespace internal {

template <typename Current>
int max_type(Current x) {
  return TYPEOF(x);
}

template <typename Current, typename... Rest>
int max_type(Current lhs, Rest... rest) {
  return max_type(lhs) >= max_type(rest...) ? max_type(lhs) : max_type(rest...);
}

}

#define CONCATENATE_CASE(RTYPE) \
  case RTYPE: { \
  Vector<RTYPE> output = no_init(n); \
  if (sizeof...(args)) { \
    do_concatenate(output, i, args...); \
  } \
  return output; \
}

template <typename... Args>
SEXP c(Args... args) {
  int maxtype = internal::max_type(args...);
  int n = get_size(args...);
  int i = 0;
  switch (maxtype) {
  CONCATENATE_CASE(INTSXP);
  CONCATENATE_CASE(REALSXP);
  CONCATENATE_CASE(STRSXP);
  CONCATENATE_CASE(LGLSXP);
  CONCATENATE_CASE(VECSXP);
  default: {
    Rprintf("Unhandled RTYPE %s encountered", Rf_type2char(maxtype));
    stop("");
  }
  }
}

}

#endif
