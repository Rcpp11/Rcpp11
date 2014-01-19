#ifndef Rcpp__stats__random_rbeta_h
#define Rcpp__stats__random_rbeta_h

namespace Rcpp {
namespace stats{
    
    class BetaGenerator : public Generator<double>{
    public: 
        BetaGenerator(double a_, double b_) : a(a_), b(b_){}
        
        inline double operator()() const {
            return ::Rf_rbeta(a, b) ;    
        }
    private:
        double a, b ;
    } ;
    
} // namespace stats

} // Rcpp

#endif
