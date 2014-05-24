#ifndef Rcpp_internal__na__h
#define Rcpp_internal__na__h

namespace Rcpp {
namespace internal {

// motivation: on 32bit architectures, we only see 'LargeNA'
// as defined ahead; on 64bit architectures, R defaults to
// 'SmallNA' for R_NaReal, but this can get promoted to 'LargeNA'
// if a certain operation can create a 'signalling' NA, e.g. NA_real_+1
static const unsigned long long SmallNA = 0x7FF00000000007A2;
static const unsigned long long LargeNA = 0x7FF80000000007A2;

struct NACanChange {
    enum { value = sizeof(void*) == 8 };
};

template <bool NACanChange>
bool is_NA__impl(double);

template <>
inline bool is_NA__impl<true>(double x) {
    return memcmp(
        (void*) &x,
        (void*) &SmallNA,
        sizeof(double)
    ) == 0 or memcmp(
        (void*) &x,
        (void*) &LargeNA,
        sizeof(double)
    ) == 0;
}

template <>
inline bool is_NA__impl<false>(double x) {
    return memcmp(
        (void*) &x,
        (void*) &LargeNA,
        sizeof(double)
    ) == 0;
}

inline bool is_NA(double x) {
  return is_NA__impl<NACanChange::value>(x);
}

// All NaN values that are not NA are considered to be
// NaN within R. In practice, we only see one kind of
// NaN value -- that is, R_NaN; however, 0/0 has a different
// kind of bitwise representation than R_NaN, and we should
// expect that software using Rcpp might encode the type of
// NaN in their output.
//
// To modify the above -- actually, we see that 0/0 and NaN
// are different values on 64bit architectures. Regardless,
// we should assume that people might encode different types
// of NaN values within R and capture those.
//
// One can test this with pryr; try using the 'bytes' and
// 'bits' functions to see what you get for NA_real_,
// NA_real_ + 1, NaN, NaN + 1, 0/0...
inline bool is_NaN(double x) {
  return std::isnan(x) && !is_NA(x);
}

}
}

#endif

