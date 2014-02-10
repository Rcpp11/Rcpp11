#ifndef Rcpp__internal__na__h
#define Rcpp__internal__na__h

namespace Rcpp {
namespace internal {

template <typename T>
bool is_NA(T x);

template <>
inline bool is_NA<double>(double x) {
  return memcmp(
    reinterpret_cast<char*>(&x),
    reinterpret_cast<char*>(&NA_REAL),
    sizeof(double)
  ) == 0;
}

template <typename T>
bool is_NaN(T x);

template <>
inline bool is_NaN<double>(double x) {
  return memcmp(
    reinterpret_cast<char*>(&x),
    reinterpret_cast<char*>(&R_NaN),
    sizeof(double)
  ) == 0;
}

}
}

#endif
