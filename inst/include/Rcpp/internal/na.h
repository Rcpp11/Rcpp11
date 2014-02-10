#ifndef Rcpp__internal__na__h
#define Rcpp__internal__na__h

namespace Rcpp {
  
namespace internal {
  
template <typename T>
bool is_NA(T x) {
  typedef typename ::Rcpp::traits::r_sexptype_traits<T>::rtype RTYPE;
  return x == ::Rcpp::traits::get_na<RTYPE>();
}

template <>
inline bool is_NA<double>(double x) {
  return memcmp(
    reinterpret_cast<void*>(&x),
    reinterpret_cast<void*>(&NA_REAL),
    sizeof(double)
  ) == 0;
}

template <typename T>
bool is_NaN(T x);

template <>
inline bool is_NaN<double>(double x) {
  return R_IsNaN(x);
}

}
}

#endif
