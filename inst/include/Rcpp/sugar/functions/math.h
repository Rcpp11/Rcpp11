#ifndef RCPP_SUGAR_MATH_H
#define RCPP_SUGAR_MATH_H

#define VECTORIZED_MATH_1(__NAME__,__SYMBOL__)                                                              \
namespace Rcpp {                                                                                            \
    template <bool HAS_NA, typename T>                                                                      \
    auto __NAME__( const SugarVectorExpression<REALSXP,HAS_NA,T>& x ) -> decltype(sapply(x, __SYMBOL__)) {  \
        return sapply( x, __SYMBOL__ ) ;                                                                    \
    }                                                                                                       \
    template <bool HAS_NA, typename T>                                                                      \
    auto __NAME__( const SugarVectorExpression<INTSXP,HAS_NA,T>& x ) -> decltype(sapply(x, __SYMBOL__)) {   \
        return sapply( x, __SYMBOL__ ) ;                                                                    \
    }                                                                                                       \
}

namespace Rcpp{                     
    namespace internal{
        inline double factorial( double x ){ return ::Rf_gammafn( x + 1.0 ) ; }
        inline double lfactorial( double x ){ return ::Rf_lgammafn( x + 1.0 ) ; }
    }
}

VECTORIZED_MATH_1(exp,::exp)
VECTORIZED_MATH_1(acos,::acos)
VECTORIZED_MATH_1(asin,::asin)
VECTORIZED_MATH_1(atan,::atan)
VECTORIZED_MATH_1(ceil,::ceil)
VECTORIZED_MATH_1(ceiling,::ceil)
VECTORIZED_MATH_1(cos,::cos)
VECTORIZED_MATH_1(cosh,::cosh)
VECTORIZED_MATH_1(floor,::floor)
VECTORIZED_MATH_1(log,::log)
VECTORIZED_MATH_1(log10,::log10)
VECTORIZED_MATH_1(sqrt,::sqrt)
VECTORIZED_MATH_1(sin,::sin)
VECTORIZED_MATH_1(sinh,::sinh)
VECTORIZED_MATH_1(tan,::tan)
VECTORIZED_MATH_1(tanh,::tanh)
VECTORIZED_MATH_1(abs,::fabs)
VECTORIZED_MATH_1(gamma      , ::Rf_gammafn     )
VECTORIZED_MATH_1(lgamma     , ::Rf_lgammafn    )
VECTORIZED_MATH_1(digamma    , ::Rf_digamma     )
VECTORIZED_MATH_1(trigamma   , ::Rf_trigamma    )
VECTORIZED_MATH_1(tetragamma , ::Rf_tetragamma  )
VECTORIZED_MATH_1(pentagamma , ::Rf_pentagamma  )
VECTORIZED_MATH_1(expm1      , ::expm1          )
VECTORIZED_MATH_1(log1p      , ::log1p          )
VECTORIZED_MATH_1(factorial  , ::Rcpp::internal::factorial   )
VECTORIZED_MATH_1(lfactorial , ::Rcpp::internal::lfactorial  )
VECTORIZED_MATH_1(trunc, ::Rf_ftrunc)

#define VECTORIZED_MATH_2(__NAME__,__SYMBOL__)                                      \
namespace Rcpp {                                                                    \
    template <typename T1, typename T2>                                             \
    auto __NAME__( T1&& x, T2&& y )                                                 \
        -> decltype(mapply(__SYMBOL__, std::forward<T1>(x), std::forward<T2>(y) ))  \
    {                                                                               \
        return mapply(__SYMBOL__, std::forward<T1>(x), std::forward<T2>(y) ) ;      \
    }                                                                               \
}

VECTORIZED_MATH_2(choose  , ::Rf_choose   )
VECTORIZED_MATH_2(lchoose , ::Rf_lchoose  )
VECTORIZED_MATH_2(beta    , ::Rf_beta     )
VECTORIZED_MATH_2(lbeta   , ::Rf_lbeta    )
VECTORIZED_MATH_2(psigamma, ::Rf_psigamma )
VECTORIZED_MATH_2(round   , ::Rf_fround   )     // rounds 'x' to 'digits' decimals digits (used by R's round())
VECTORIZED_MATH_2(signif  , ::Rf_fprec    )     // rounds 'x' to 'digits' significant digits (used by R's signif())

#endif
