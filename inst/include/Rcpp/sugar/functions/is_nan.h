#ifndef Rcpp__sugar__is_nan_h
#define Rcpp__sugar__is_nan_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename VEC_TYPE>
class IsNaN : public SugarVectorExpression< LGLSXP, false, IsNaN<RTYPE,NA,VEC_TYPE> > {
public:

	IsNaN( const VEC_TYPE& obj_) : obj(obj_){}

	inline int operator[]( int i ) const {
		return ::Rcpp::traits::is_nan<RTYPE>( obj[i] ) ;
	}

	inline int size() const { return obj.size() ; }

private:
	const VEC_TYPE& obj ;

} ;


} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::IsNaN<RTYPE,NA,T> is_nan( const Rcpp::VectorBase<RTYPE,NA,T>& t){
	return sugar::IsNaN<RTYPE,NA,T>( t.get_ref() ) ;
}

} // Rcpp
#endif

