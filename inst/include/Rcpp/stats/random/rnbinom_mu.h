#ifndef Rcpp__stats__random_rnbinom_mu_h
#define Rcpp__stats__random_rnbinom_mu_h

namespace Rcpp {
	namespace stats {


		class NBinomGenerator_Mu : public ::Rcpp::Generator<double> {
		public:

			NBinomGenerator_Mu( double siz_, double mu_ ) : 
				siz(siz_), lambda( mu_ / siz_ ) {}

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
