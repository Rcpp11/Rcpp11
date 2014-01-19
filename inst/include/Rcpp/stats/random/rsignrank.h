#ifndef Rcpp__stats__random_rsignrank_h
#define Rcpp__stats__random_rsignrank_h

namespace Rcpp {
    namespace stats{
    
        
		class SignRankGenerator : public Generator<double>{
		public:
		    SignRankGenerator(double nn_) : nn(nn_){}
		    inline double operator()() const { return ::Rf_rsignrank(nn) ; }
		private:
		    double nn ;
		} ;
    } // stats

} // Rcpp

#endif
