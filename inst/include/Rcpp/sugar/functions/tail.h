#ifndef Rcpp__sugar__tail_h
#define Rcpp__sugar__tail_h

namespace Rcpp{
namespace sugar{
	
template <int RTYPE, bool NA, typename T>
class Tail : public Rcpp::VectorBase< RTYPE ,NA, Tail<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Tail( const VEC_TYPE& object_, int n_ ) : object(object_), start(0), n(n_) {
		if( n > 0 ){
			start = object.size() - n ;
		} else {
			start = -n ;
			n = object.size() - start ;
		}
	}
	
	inline STORAGE operator[]( int i ) const {
		return object[ start + i ] ;
	}
	inline int size() const { return n; }
	         
private:
	const VEC_TYPE& object ;
	int start, n ;
} ;
	
} // sugar

template <int RTYPE,bool NA, typename T>
inline sugar::Tail<RTYPE,NA,T> tail( 
	const VectorBase<RTYPE,NA,T>& t, 
	int n 
	){
	return sugar::Tail<RTYPE,NA,T>( t, n ) ;
}

} // Rcpp
#endif

