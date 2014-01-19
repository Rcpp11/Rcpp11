#ifndef Rcpp__stats__random_rgeom_h
#define Rcpp__stats__random_rgeom_h

namespace Rcpp {
	namespace stats {

	    
		class GeomGenerator : public ::Rcpp::Generator<double> {
		public:
	
			GeomGenerator( double p ) : lambda( (1-p)/p  ) {}
	
			inline double operator()() const {
				return ::Rf_rpois(exp_rand() * lambda); 
			}
	
		private:
			double lambda ;
		} ;
	} // stats

} // Rcpp

#endif
