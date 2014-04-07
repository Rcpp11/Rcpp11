#ifndef Rcpp__sugar__rev_h
#define Rcpp__sugar__rev_h

namespace Rcpp{
namespace sugar{
	
template <int RTYPE, bool NA, typename T>
class Rev : public SugarVectorExpression< RTYPE ,NA, Rev<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Rev( const VEC_TYPE& object_ ) : 
		object(object_), n(object_.size() - 1) {}
	
	inline STORAGE operator[]( int i ) const {
		return object[n - i] ;
	}
	inline int size() const { return n + 1; }
	         
private:
	const VEC_TYPE& object ;
	int n ;
} ;
	
} // sugar

template <int RTYPE,bool NA, typename T>
inline sugar::Rev<RTYPE,NA,T> rev( const VectorBase<RTYPE,NA,T>& t){
	return sugar::Rev<RTYPE,NA,T>( t ) ;
}

} // Rcpp
#endif

