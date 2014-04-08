#ifndef Rcpp__stats__random_rlogis_h
#define Rcpp__stats__random_rlogis_h

namespace Rcpp {
    namespace stats {


        class LogisGenerator : public ::Rcpp::Generator<double> {
        public:

            LogisGenerator( double location_, double scale_ ) : 
                location(location_), scale(scale_) {}

            inline double operator()() const {
                double u = unif_rand() ;
                return location + scale * ::log(u / (1. - u));
            }

        private:
            double location ;
            double scale ;
        } ;

    
        class LogisGenerator_1 : public ::Rcpp::Generator<double> {
        public:

            LogisGenerator_1( double location_) : 
                location(location_) {}

            inline double operator()() const {
                double u = unif_rand() ;
                return location + ::log(u / (1. - u));
            }

        private:
            double location ;
        } ;

    
        class LogisGenerator_0 : public ::Rcpp::Generator<double> {
        public:

            LogisGenerator_0() {}

            inline double operator()() const {
                double u = unif_rand() ;
                return ::log(u / (1. - u));
            }

        } ;

    } // stats

} // Rcpp

#endif
