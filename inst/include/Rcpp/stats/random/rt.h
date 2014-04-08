#ifndef Rcpp__stats__random_rt_h
#define Rcpp__stats__random_rt_h

namespace Rcpp {
    namespace stats {


        class TGenerator : public ::Rcpp::Generator<double> {
        public:

            TGenerator( double df_ ) : df(df_), df_2(df_/2.0) {}

            inline double operator()() const {
                /* Some compilers (including MW6) evaluated this from right to left
                   return norm_rand() / sqrt(rchisq(df) / df); */
                double num = norm_rand();
    
                // return num / sqrt(rchisq(df) / df);
                // replaced by the followoing line to skip the test in 
                // rchisq because we already know
                return num / ::sqrt( ::Rf_rgamma(df_2, 2.0) / df);
            }

        private:
            double df, df_2 ;
        } ;
    } // stats

} // Rcpp

#endif
