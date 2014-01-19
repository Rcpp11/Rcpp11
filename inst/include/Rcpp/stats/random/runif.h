#ifndef Rcpp__stats__random_runif_h
#define Rcpp__stats__random_runif_h

namespace Rcpp {
	namespace stats {

		
		class UnifGenerator : public ::Rcpp::Generator<double> {
		public:
	
			UnifGenerator( double min_ = 0.0, double max_ = 1.0) : 
				min(min_), diff(max_ - min_) {}
	
			inline double operator()() const {
				double u;
				do {u = unif_rand();} while (u <= 0 || u >= 1);
				return min + diff * u;
			}
	
		private:
			double min; 
			double diff ;
		} ;

		
		class UnifGenerator__0__1 : public ::Rcpp::Generator<double> {
		public:
	
			UnifGenerator__0__1() {}
	
			inline double operator()() const {
				double u;
				do {u = unif_rand();} while (u <= 0 || u >= 1);
				return u;
			}
		} ;
	} // stats

} // Rcpp

#endif
