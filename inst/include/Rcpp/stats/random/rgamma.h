#ifndef Rcpp__stats__random_rgamma_h
#define Rcpp__stats__random_rgamma_h

namespace Rcpp {
    namespace stats {
        
        class GammaGenerator : public Generator<double>{
        public:
            GammaGenerator(double a_, double scale_) : 
                a(a_), scale(scale_) {}
            inline double operator()() const { return ::Rf_rgamma(a, scale ) ;}    
        private:
            double a, scale ;
        } ;
    }    // stats
    

} // Rcpp

#endif
