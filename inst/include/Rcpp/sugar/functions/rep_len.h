#ifndef Rcpp__sugar__rep_len_h
#define Rcpp__sugar__rep_len_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Rep_len : public SugarVectorExpression< RTYPE ,NA, Rep_len<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Rep_len( const VEC_TYPE& object_, int len_ ) : 
		object(object_), len(len_), n(object_.size()){}
	
	inline STORAGE operator[]( int i ) const {
		return object[ i % n ] ;
	}
	inline int size() const { return len ; }
	         
private:
	const VEC_TYPE& object ;
	int len, n ;
} ;
	
} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::Rep_len<RTYPE,NA,T> rep_len( const VectorBase<RTYPE,NA,T>& t, int len ){
	return sugar::Rep_len<RTYPE,NA,T>( t, len ) ;
}


} // Rcpp
#endif

