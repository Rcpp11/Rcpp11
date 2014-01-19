#ifndef Rcpp__stats__random_rhyper_h
#define Rcpp__stats__random_rhyper_h

namespace Rcpp {
    namespace stats {
        
        class HyperGenerator : public Generator<double>{
        public:
            HyperGenerator( double nn1_, double nn2_, double kk_) : 
                nn1(nn1_), nn2(nn2_), kk(kk_){}
            inline double operator()() const { return ::Rf_rhyper(nn1, nn2, kk) ;}  
        private:
            double nn1, nn2, kk ;
        } ;
    }
    
} // Rcpp

#endif
