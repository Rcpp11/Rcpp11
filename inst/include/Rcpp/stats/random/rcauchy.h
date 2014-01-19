#ifndef Rcpp__stats__random_rcauchy_h
#define Rcpp__stats__random_rcauchy_h

namespace Rcpp {
namespace stats {

class CauchyGenerator : public ::Rcpp::Generator<double> {
public:
	
	CauchyGenerator( double location_, double scale_) : 
		location(location_) , scale(scale_) {}
	
	inline double operator()() const {
		return location + scale * ::tan(M_PI * unif_rand()) ;
	}
	
private:
	double location, scale ;
} ;

class CauchyGenerator_1 : public ::Rcpp::Generator<double> {
public:
	
	CauchyGenerator_1( double location_) : 
		location(location_){}
	
	inline double operator()() const {
		return location + ::tan(M_PI * unif_rand()) ;
	}
	
private:
	double location ;
} ;

class CauchyGenerator_0 : public ::Rcpp::Generator<double> {
public:
	
	CauchyGenerator_0(){}
	
	inline double operator()() const {
		return ::tan(M_PI * unif_rand()) ;
	}
	
} ;

} // stats

} // Rcpp

#endif
