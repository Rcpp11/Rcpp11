#ifndef Rcpp__stats__random_rlnorm_h
#define Rcpp__stats__random_rlnorm_h

namespace Rcpp {
	namespace stats {


		class LNormGenerator : public Generator<double> {
		public:

			LNormGenerator( double meanlog_ = 0.0 , double sdlog_ = 1.0 ) : 
				meanlog(meanlog_), sdlog(sdlog_) {}

			inline double operator()() const {
				return ::exp( meanlog + sdlog * ::norm_rand() ) ;
			}

		private:
			double meanlog ;
			double sdlog ;
		} ;

	
		class LNormGenerator_1 : public Generator<double> {
		public:

			LNormGenerator_1( double meanlog_ = 0.0 ) : 
				meanlog(meanlog_) {}

			inline double operator()() const {
				return ::exp( meanlog + ::norm_rand() ) ;
			}

		private:
			double meanlog ;
		} ;

	
		class LNormGenerator_0 : public Generator<double> {
		public:

			LNormGenerator_0( ) {}

			inline double operator()() const {
				return ::exp(::norm_rand() ) ;
			}

		} ;

	} // stats

} // Rcpp

#endif
