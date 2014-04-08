#ifndef Rcpp__stats__random_rnbinom_h
#define Rcpp__stats__random_rnbinom_h

namespace Rcpp {
    namespace stats {


        class NBinomGenerator : public ::Rcpp::Generator<double> {
        public:

            NBinomGenerator( double siz_, double prob_ ) : 
                siz(siz_), lambda( (1-prob_)/prob_ ) {}

            inline double operator()() const {
                return ::Rf_rpois( ::Rf_rgamma( siz, lambda ) ) ; 
            }

        private:
            double siz ;
            double lambda ;
        } ;
    } // stats

} // Rcpp

#endif
