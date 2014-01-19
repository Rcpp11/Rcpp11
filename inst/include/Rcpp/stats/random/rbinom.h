#ifndef Rcpp__stats__random_rbinom_h
#define Rcpp__stats__random_rbinom_h

namespace Rcpp {
namespace stats {
    
    class BinomGenerator : public Generator<double>{
    public:
        BinomGenerator( double nin_, double pp_ ) : nin(nin_), pp(pp_){}
        inline double operator()() const{
            return ::Rf_rbinom( nin, pp ) ;    
        }
    private:
        double nin, pp ;
    } ;
    
}  // stats
    
} // Rcpp

#endif
