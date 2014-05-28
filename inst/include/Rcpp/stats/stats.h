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

RCPP_DPQ__1(chisq,double df = 1, df )
RCPP_DPQ__2(beta,double a, double b,a,b)
RCPP_DPQ__2(binom,double n, double p, n, p)

#undef RCPP_CONCAT
#undef RCPP_ECHO


#include <Rcpp/stats/dpq/dpq.h>

#define ML_POSINF    R_PosInf
#define ML_NEGINF    R_NegInf
#define ML_NAN        R_NaN

// RCPP_DPQ_2(beta,::Rf_dbeta,::Rf_pbeta,::Rf_qbeta)
// RCPP_DPQ_2(binom,::Rf_dbinom,::Rf_pbinom,::Rf_qbinom)
// RCPP_DPQ_1(chisq,::Rf_dchisq,::Rf_pchisq,::Rf_qchisq)
RCPP_DPQ_2(f,::Rf_df,::Rf_pf,::Rf_qf)
RCPP_DPQ_1(geom, ::Rf_dgeom, ::Rf_pgeom, ::Rf_qgeom )
RCPP_DPQ_3(hyper,::Rf_dhyper,::Rf_phyper,::Rf_qhyper)
RCPP_DPQ_3(nbeta,::Rf_dnbeta,::Rf_pnbeta,::Rf_qnbeta)
RCPP_DPQ_2(nbinom, ::Rf_dnbinom, ::Rf_pnbinom, ::Rf_qnbinom )
RCPP_DPQ_2(nbinom_mu,::dnbinom_mu, ::pnbinom_mu, ::qnbinom_mu )
RCPP_DPQ_2( nchisq, ::Rf_dnchisq, ::Rf_pnchisq, ::Rf_qnchisq )
RCPP_DPQ_3(nf,::Rf_dnf,::Rf_pnf,::Rf_qnf)
RCPP_DPQ_2(nt,::Rf_dnt,::Rf_pnt,::Rf_qnt)
RCPP_DPQ_1(pois,::Rf_dpois,::Rf_ppois,::Rf_qpois)
RCPP_DPQ_1(t, ::Rf_dt, ::Rf_pt, ::Rf_qt)

#include <Rcpp/stats/cauchy.h>
#include <Rcpp/stats/exp.h>
#include <Rcpp/stats/gamma.h>
#include <Rcpp/stats/logis.h>
#include <Rcpp/stats/norm.h>
#include <Rcpp/stats/lnorm.h>
#include <Rcpp/stats/unif.h>
#include <Rcpp/stats/weibull.h>

#include <Rcpp/stats/random/random.h>

#endif
