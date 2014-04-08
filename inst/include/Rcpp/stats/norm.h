#ifndef Rcpp__stats__norm_h
#define Rcpp__stats__norm_h

namespace Rcpp {
namespace stats {

inline double dnorm_1(double x, double mu /*, double sigma [=1.0]*/ , int give_log) {
#ifdef IEEE_754
    if (ISNAN(x) || ISNAN(mu) )
	return x + mu + 1.0 ;
#endif
    if(!R_FINITE(x) && mu == x) return ML_NAN;/* x-mu is NaN */
    x = (x - mu) ;

    if(!R_FINITE(x)) return R_D__0;
    return (give_log ?
	    -(M_LN_SQRT_2PI  +	0.5 * x * x ) :
	    M_1_SQRT_2PI * ::exp(-0.5 * x * x) );
    /* M_1_SQRT_2PI = 1 / sqrt(2 * pi) */
}

inline double dnorm_0(double x /*, double mu [=0.0], double sigma [=1.0]*/ , int give_log) {
#ifdef IEEE_754
    if (ISNAN(x) )
	return x + 1.0 ;
#endif
   	if(!R_FINITE(x)) return R_D__0;
    return (give_log ?
	    -(M_LN_SQRT_2PI  +	0.5 * x * x ) :
	    M_1_SQRT_2PI * ::exp(-0.5 * x * x) );
    /* M_1_SQRT_2PI = 1 / sqrt(2 * pi) */
}

inline double pnorm_1(double x, double mu /*, double sigma [=1.]*/ , int lower_tail, int log_p){
    double p, cp;

    /* Note: The structure of these checks has been carefully thought through.
     * For example, if x == mu and sigma == 0, we get the correct answer 1.
     */
#ifdef IEEE_754
    if(ISNAN(x) || ISNAN(mu) )
	return x + mu + 1.0 ;
#endif
    if(!R_FINITE(x) && mu == x) return ML_NAN;/* x-mu is NaN */
    p = (x - mu) ;
    if(!R_FINITE(p))
	return (x < mu) ? R_DT_0 : R_DT_1;
    x = p;

    ::Rf_pnorm_both(x, &p, &cp, (lower_tail ? 0 : 1), log_p);

    return(lower_tail ? p : cp);
}

inline double pnorm_0(double x /*, double mu [=0.] , double sigma [=1.]*/ , int lower_tail, int log_p) {
    double p, cp;

    /* Note: The structure of these checks has been carefully thought through.
     * For example, if x == mu and sigma == 0, we get the correct answer 1.
     */
#ifdef IEEE_754
    if(ISNAN(x)  )
	return x + 1.0 ;
#endif
    p = x ;
    if(!R_FINITE(p))
	return (x < 0.0 ) ? R_DT_0 : R_DT_1;
    x = p;

    ::Rf_pnorm_both(x, &p, &cp, (lower_tail ? 0 : 1), log_p);

    return(lower_tail ? p : cp);
}

inline double qnorm_1(double p, double mu /*, double sigma [=1.] */, int lower_tail, int log_p){
	return ::Rf_qnorm5(p, mu, 1.0, lower_tail, log_p ) ;
}
inline double qnorm_0(double p /*, double mu [=0.], double sigma [=1.] */, int lower_tail, int log_p){
	return ::Rf_qnorm5(p, 0.0, 1.0, lower_tail, log_p ) ;
}

} // stats
} // Rcpp

RCPP_DPQ_0(norm, Rcpp::stats::dnorm_0, Rcpp::stats::pnorm_0, Rcpp::stats::qnorm_0 )
RCPP_DPQ_1(norm, Rcpp::stats::dnorm_1, Rcpp::stats::pnorm_1, Rcpp::stats::qnorm_1 )
RCPP_DPQ_2(norm, ::Rf_dnorm4, ::Rf_pnorm5, ::Rf_qnorm5 )

#endif
