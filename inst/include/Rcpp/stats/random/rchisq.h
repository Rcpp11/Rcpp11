#ifndef Rcpp__stats__random_rchisq_h
#define Rcpp__stats__random_rchisq_h

namespace Rcpp {
	namespace stats {
		
	    
		class ChisqGenerator : public ::Rcpp::Generator<double> {
		public:
			
			ChisqGenerator( double df_ ) : df_2(df_ / 2.0) {}
			
			inline double operator()() const {
				return ::Rf_rgamma( df_2, 2.0 ) ; 
			}
			
		private:
			double df_2 ;
		} ;
	} // stats

} // Rcpp

#endif
