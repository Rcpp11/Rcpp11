#ifndef Rcpp__stats__random_rweibull_h
#define Rcpp__stats__random_rweibull_h

namespace Rcpp {
	namespace stats {

		
		class WeibullGenerator : public ::Rcpp::Generator<double> {
		public:
	
			WeibullGenerator( double shape_, double scale_ ) : 
				shape_inv( 1/shape_), scale(scale_) {}
	
			inline double operator()() const {
				return scale * ::R_pow(-::log(unif_rand()), shape_inv );
			}
	
		private:
			double shape_inv, scale ; 
		} ;
		
		
		class WeibullGenerator__scale1 : public ::Rcpp::Generator<double> {
		public:
	
			WeibullGenerator__scale1( double shape_ ) : 
				shape_inv( 1/shape_) {}
	
			inline double operator()() const {
				return ::R_pow(-::log(unif_rand()), shape_inv );
			}
	
		private:
			double shape_inv ; 
		} ;
	} // stats

} // Rcpp

#endif
