#ifndef Rcpp_traits_static_max_int_h_
#define Rcpp_traits_static_max_int_h_

namespace Rcpp {
  
namespace traits {

template <int T1>
constexpr int static_max_int__() {
  return T1;
}

template <int T1, int T2, int... Args>
constexpr int static_max_int__() {
  return T1 > T2 ? static_max_int__<T1, Args...>() : static_max_int__<T2, Args...>();
}

// the struct to hold the value in a traits-like fashion
// so we can do e.g. template_max<1, 2, 3>::value
template <int T1, int T2, int... Args>
struct static_max {
  enum { value = T1 > T2 ? static_max_int__<T1, Args...>() : static_max_int__<T2, Args...>() };
};

} // traits
  
} // Rcpp

#endif