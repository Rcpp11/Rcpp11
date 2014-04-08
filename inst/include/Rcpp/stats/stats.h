#ifndef Rcpp__stats__stats_h
#define Rcpp__stats__stats_h

#include <Rcpp/stats/dpq/dpq.h>

#define ML_POSINF    R_PosInf
#define ML_NEGINF    R_NegInf
#define ML_NAN        R_NaN

RCPP_DPQ_2(beta,::Rf_dbeta,::Rf_pbeta,::Rf_qbeta)
RCPP_DPQ_2(binom,::Rf_dbinom,::Rf_pbinom,::Rf_qbinom)
RCPP_DPQ_1(chisq,::Rf_dchisq,::Rf_pchisq,::Rf_qchisq)
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
