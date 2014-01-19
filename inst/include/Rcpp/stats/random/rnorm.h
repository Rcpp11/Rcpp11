#ifndef Rcpp__stats__random_rnorm_h
#define Rcpp__stats__random_rnorm_h

namespace Rcpp {
	namespace stats {

	    
		class NormGenerator : public Generator<double> {
		public:
	
			NormGenerator( double mean_ = 0.0 , double sd_ = 1.0 ) : 
				mean(mean_), sd(sd_) {}
	
			inline double operator()() const {
				return mean + sd * ::norm_rand() ;
			}
	
		private:
			double mean ;
			double sd ;
		} ;


		
		class NormGenerator__sd1 : public Generator<double> {
		public:
	
			NormGenerator__sd1( double mean_ = 0.0 ) : mean(mean_) {}
	
			inline double operator()() const {
				return mean + ::norm_rand() ;
			}
	
		private:
			double mean ;
		} ;


		
		class NormGenerator__mean0 : public Generator<double> {
		public:
	
			NormGenerator__mean0( double sd_ = 1.0 ) : sd(sd_) {}
	
			inline double operator()() const {
				return sd * ::norm_rand() ;
			}
	
		private:
			double sd ;
		} ;

		
		class NormGenerator__mean0__sd1 : public Generator<double> {
		public:
	
			NormGenerator__mean0__sd1( ) {}
	
			inline double operator()() const {
				return ::norm_rand() ;
			}
	
		} ;
		
	} // stats


	
} // Rcpp

#endif
