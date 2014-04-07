#ifndef Rcpp__sugar__head_h
#define Rcpp__sugar__head_h

namespace Rcpp{
namespace sugar{
	
template <int RTYPE, bool NA, typename T>
class Head : public SugarVectorExpression< RTYPE ,NA, Head<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Head( const VEC_TYPE& object_, int n_ ) : object(object_), n(n_) {
		if( n < 0 ){
			n = object.size() + n ;
		}
	}
	
	inline STORAGE operator[]( int i ) const {
		return object[ i ] ;
	}
	inline int size() const { return n; }
	         
private:
	const VEC_TYPE& object ;
	int n ;
} ;
	
} // sugar

template <int RTYPE,bool NA, typename T>
inline sugar::Head<RTYPE,NA,T> head( 
	const VectorBase<RTYPE,NA,T>& t, 
	int n 
	){
	return sugar::Head<RTYPE,NA,T>( t, n ) ;
}

} // Rcpp
#endif

