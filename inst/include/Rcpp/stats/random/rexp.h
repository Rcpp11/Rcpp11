#ifndef Rcpp__stats__random_rexp_h
#define Rcpp__stats__random_rexp_h

namespace Rcpp {
	namespace stats {


		class ExpGenerator : public ::Rcpp::Generator<double> {
		public:

			ExpGenerator( double scale_ ) : scale(scale_) {}

			inline double operator()() const {
				return scale * exp_rand() ;
			}

		private:
			double scale ;
		} ;
	
	
		class ExpGenerator__rate1 : public Generator<double>{
		public:
		    ExpGenerator__rate1(){}
		    inline double operator()() const { return exp_rand() ; }
		} ;

	} // stats

}

#endif
