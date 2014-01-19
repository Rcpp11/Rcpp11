#ifndef Rcpp__stats__random_rpois_h
#define Rcpp__stats__random_rpois_h

namespace Rcpp {
    namespace stats{
        
        
    	class PoissonGenerator : public Generator<double>{
    	public:
    	    PoissonGenerator( double mu_ ) : mu(mu_){}  
    	    inline double operator()() const { return ::Rf_rpois(mu); }
    	private:
    	    double mu ;
    	} ;
    }  // stats

} // Rcpp

#endif
