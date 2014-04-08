#ifndef Rcpp__sugar__is_finite_h
#define Rcpp__sugar__is_finite_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename VEC_TYPE>
class IsFinite : public SugarVectorExpression< LGLSXP, false, IsFinite<RTYPE,NA,VEC_TYPE> > {
public:

	IsFinite( const VEC_TYPE& obj_) : obj(obj_){}

	inline int operator[]( int i ) const {
		return ::Rcpp::traits::is_finite<RTYPE>( obj[i] ) ;
	}

	inline int size() const { return obj.size() ; }

private:
	const VEC_TYPE& obj ;

} ;


} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::IsFinite<RTYPE,NA,T> is_finite( const Rcpp::VectorBase<RTYPE,NA,T>& t){
	return sugar::IsFinite<RTYPE,NA,T>( t.get_ref() ) ;
}

} // Rcpp
#endif

