#ifndef Rcpp__stats__stats_h
#define Rcpp__stats__stats_h

#define RCPP_DPQ(__NAME__,PAR,VAL)                                                                      \
namespace Rcpp{                                                                                         \
    template <int RTYPE,bool HAS_NA, typename T>                                                                  \
    auto d##__NAME__( const SugarVectorExpression<RTYPE,HAS_NA,T>& x, PAR, int give_log = false ) ->  \
        decltype(sapply( x, ::Rf_d##__NAME__, VAL, give_log ))                                          \
    {                                                                                                   \
        return sapply( x, ::Rf_d##__NAME__, VAL, give_log ) ;                                                      \
    }                                                                                                   \
    template <int RTYPE, bool HAS_NA, typename T>                                                                  \
    auto p##__NAME__( const SugarVectorExpression<RTYPE,HAS_NA,T>& x, PAR, bool lower = true, bool log = false ) ->  \
        decltype(sapply( x, ::Rf_p##__NAME__, VAL, lower, log ))                                          \
    {                                                                                                   \
        return sapply( x, ::Rf_p##__NAME__, VAL, lower, log ) ;                                                      \
    }                                                                                                   \
    template <int RTYPE, bool HAS_NA, typename T>                                                                  \
    auto q##__NAME__( const SugarVectorExpression<RTYPE,HAS_NA,T>& x, PAR, bool lower = true, bool log = false ) ->  \
        decltype(sapply( x, ::Rf_q##__NAME__, VAL, lower, log ))                                          \
    {                                                                                                   \
        return sapply( x, ::Rf_q##__NAME__, VAL, lower, log ) ;                                                      \
    }                                                                                                   \
}                      

#define RCPP_CONCAT(...) __VA_ARGS__
#define RCPP_ECHO(X) X

#define RCPP_DPQ__1 RCPP_DPQ
#define RCPP_DPQ__2(__NAME__,PAR1,PAR2,VAL1,VAL2) RCPP_DPQ(__NAME__,RCPP_ECHO(RCPP_CONCAT(PAR1,PAR2)), RCPP_ECHO(RCPP_CONCAT(VAL1,VAL2)) )
#define RCPP_DPQ__3(__NAME__,PAR1,PAR2,PAR3,VAL1,VAL2,VAL3) RCPP_DPQ(__NAME__,RCPP_ECHO(RCPP_CONCAT(PAR1,PAR2,PAR3)), RCPP_ECHO(RCPP_CONCAT(VAL1,VAL2,VAL3)) )

RCPP_DPQ__1(chisq,double df = 1, df )
RCPP_DPQ__2(beta ,double a, double b,a,b)
RCPP_DPQ__2(binom,double n, double p, n, p)
RCPP_DPQ__2(f,double m, double n, m, n)
RCPP_DPQ__1(geom,double p, p)
RCPP_DPQ__3(hyper,double r, double b, double n, r, b, n)
RCPP_DPQ__3(nbeta,double a, double b, double ncp, a, b, ncp)
RCPP_DPQ__2(nbinom,double size, double prob, size, prob)
RCPP_DPQ__3(nbinom_mu,double size, double prob, double mu, size, prob, mu)
RCPP_DPQ__2(nchisq,double df, double ncp, df, ncp)
RCPP_DPQ__3(nf,double df1, double df2, double ncp, df1, df2, ncp)
RCPP_DPQ__2(nt,double df, double ncp, df, ncp)
RCPP_DPQ__1(pois,double lambda, lambda)
RCPP_DPQ__1(t,double n, n)
RCPP_DPQ__2(cauchy,double location = 0, double scale = 1, location, scale)
RCPP_DPQ__1(exp,double rate, 1.0 / rate )
RCPP_DPQ__2(gamma,double shape = 0, double rate = 1, shape, 1.0/rate )
RCPP_DPQ__2(logis,double location = 0, double scale = 1, location, scale )
#define Rf_dnorm Rf_dnorm4
#define Rf_pnorm Rf_pnorm5
#define Rf_qnorm Rf_qnorm5
RCPP_DPQ__2(norm,double mean = 0, double sd = 1, mean, sd )
#undef Rf_dnorm
#undef Rf_pnorm
#undef Rf_qnorm
RCPP_DPQ__2(lnorm,double meanlog = 0, double sdlog = 1, meanlog, sdlog )
RCPP_DPQ__2(unif,double a = 0, double b = 1, a, b )
RCPP_DPQ__2(weibull,double shape, double scale = 1, shape, scale )

#undef RCPP_CONCAT
#undef RCPP_ECHO

#include <Rcpp/stats/random/random.h>

#endif
