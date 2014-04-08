#ifndef Rcpp__stats__random_rf_h
#define Rcpp__stats__random_rf_h

namespace Rcpp {
    namespace stats {


        class FGenerator_Finite_Finite : public ::Rcpp::Generator<double> {
        public:

            FGenerator_Finite_Finite( double n1_, double n2_ ) : 
                n1__2(n1_ / 2.0 ), n2__2(n2_ / 2.0 ), ratio(n2_/n1_) {}

            inline double operator()() const {
                // here we know that both n1 and n2 are finite
                // return ( ::rchisq( n1 ) / n1 ) / ( ::rchisq( n2 ) / n2 );
                return ratio * ::Rf_rgamma( n1__2, 2.0 ) / ::Rf_rgamma( n2__2, 2.0 ) ;
            }

        private:
            double n1__2, n2__2, ratio ;
        } ;

    
        class FGenerator_NotFinite_Finite : public ::Rcpp::Generator<double> {
        public:

            FGenerator_NotFinite_Finite( double n2_ ) : n2( n2_), n2__2(n2_ / 2.0 ) {}

            inline double operator()() const {
                // return n2  / ::rchisq( n2 ) ;
                return n2 / ::Rf_rgamma( n2__2, 2.0 ) ;
            }

        private:
            double n2, n2__2 ;
        } ;

    
        class FGenerator_Finite_NotFinite : public ::Rcpp::Generator<double> {
        public:

            FGenerator_Finite_NotFinite( double n1_ ) : n1(n1_), n1__2(n1_ / 2.0 ) {}

            inline double operator()() const {
                // return ::rchisq( n1 ) / n1 ;
                return ::Rf_rgamma( n1__2, 2.0 ) / n1 ;
            }

        private:
            double n1, n1__2 ;
        } ;

    } // stats 

} // Rcpp

#endif
