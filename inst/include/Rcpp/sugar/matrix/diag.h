#ifndef Rcpp__sugar__diag_h
#define Rcpp__sugar__diag_h

namespace Rcpp{	
namespace sugar{
	
template <int RTYPE, bool NA, typename T>
class Diag_Extractor : public Rcpp::VectorBase< RTYPE ,NA, Diag_Extractor<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::MatrixBase<RTYPE,NA,T> MAT_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Diag_Extractor( const MAT_TYPE& object_ ) : object(object_), n(0) {
		int nr = object.nrow() ;
		int nc = object.ncol() ;
		n = (nc < nr ) ? nc : nr ;
	}
	
	inline STORAGE operator[]( int i ) const {
		return object( i, i ) ;
	}
	inline int size() const { return n; }
	         
private:
	const MAT_TYPE& object ;
	int n ;
} ;
	

template <int RTYPE, bool NA, typename T>
class Diag_Maker : public Rcpp::MatrixBase< RTYPE ,NA, Diag_Maker<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Diag_Maker( const VEC_TYPE& object_ ) : object(object_), n(object_.size()) {}
	
	inline STORAGE operator()( int i, int j ) const {
		return (i==j) ? object[i] : 0 ;
	}
	inline int size() const { return n * n; }
	inline int ncol() const { return n; }
	inline int nrow() const { return n; }
	         
private:
	const VEC_TYPE& object ;
	int n ;
} ;

template <typename T> struct diag_result_type_trait{
	typedef typename std::conditional<
		Rcpp::traits::matrix_interface<T>::value, 
		Diag_Extractor< T::r_type::value , T::can_have_na::value , T >, 
		Diag_Maker< T::r_type::value , T::can_have_na::value , T > 
	>::type type ;
} ;

} // sugar

template <typename T>
inline typename sugar::diag_result_type_trait<T>::type 
diag( const T& t ){
	return typename sugar::diag_result_type_trait<T>::type( t ) ;
}


} // Rcpp
#endif

