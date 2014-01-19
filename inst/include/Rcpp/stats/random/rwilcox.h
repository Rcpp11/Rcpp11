#ifndef Rcpp__stats__random_rwilcox_h
#define Rcpp__stats__random_rwilcox_h

namespace Rcpp {
    namespace stats {
        
        class WilcoxGenerator : public Generator<double>{
        public:
            WilcoxGenerator( double mm_, double nn_) : mm(mm_), nn(nn_){} 
            inline double operator()() const { return ::Rf_rwilcox(mm,nn); }
        private:
            double mm, nn ;
        } ;
    } // stats    

} // Rcpp

#endif
