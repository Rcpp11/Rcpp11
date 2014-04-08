#ifndef Rcpp__stats__random_rnchisq_h
#define Rcpp__stats__random_rnchisq_h

namespace Rcpp {
    namespace stats {

    
        class NChisqGenerator : public ::Rcpp::Generator<double> {
        public:

            NChisqGenerator( double df_, double lambda_ ) : 
                df(df_), df_2(df_ / 2.0), lambda_2(lambda_ / 2.0 ) {}

            inline double operator()() const {
                double r = ::Rf_rpois( lambda_2 ) ;
                // if( r > 0.0 ) r = Rf_rchisq( 2. * r ) ;
                // replace by so that we can skip the tests in rchisq
                // because there is no point in doing them as we know the 
                // outcome for sure
                if( r > 0.0 ) r = ::Rf_rgamma( r, 2. ) ;
                if (df > 0.) r += ::Rf_rgamma( df_2, 2.);
                return r;
            }

        private:
            double df ;
            double df_2 ;
            double lambda_2 ;
        } ;
    } // stats

} // Rcpp

#endif
