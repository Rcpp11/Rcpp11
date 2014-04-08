#ifndef Rcpp__sugar__sum_h
#define Rcpp__sugar__sum_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Sum : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Sum<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	typedef typename Rcpp::traits::Extractor< RTYPE, NA, T>::type VEC_EXT ;
	
	Sum( const VEC_TYPE& object_ ) : object(object_.get_ref()){}

	STORAGE get() const {
		STORAGE result = 0 ;
		int n = object.size() ;
		STORAGE current ;
		for( int i=0; i<n; i++){
		    current = object[i] ;
		    if( Rcpp::traits::is_na<RTYPE>(current) ) 
		        return Rcpp::traits::get_na<RTYPE>() ;
		    result += current ;
		}
		return result ;
	}         
private:
	const VEC_EXT& object ;
} ;
// RTYPE = REALSXP
template <bool NA, typename T>
class Sum<REALSXP,NA,T> : public Lazy< double , Sum<REALSXP,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<REALSXP,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::Extractor< REALSXP, NA, T>::type VEC_EXT ;
	
	Sum( const VEC_TYPE& object_ ) : object(object_.get_ref()){}

	double get() const {
		double result = 0 ;
		int n = object.size() ;
		for( int i=0; i<n; i++){
		   result += object[i] ;
		}
		return result ;
	}         
private:
	const VEC_EXT& object ;
} ;


template <int RTYPE, typename T>
class Sum<RTYPE,false,T> : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Sum<RTYPE,false,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,false,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	typedef typename Rcpp::traits::Extractor< RTYPE, false, T>::type VEC_EXT ;

	Sum( const VEC_TYPE& object_ ) : object(object_.get_ref()){}

	STORAGE get() const {
		STORAGE result = 0 ;
		int n = object.size() ;
		for( int i=0; i<n; i++){
		    result += object[i] ;
		}
		return result ;
	}         
private:
	const VEC_EXT& object ;
} ;

} // sugar

template <bool NA, typename T>
inline sugar::Sum<INTSXP,NA,T> sum( const VectorBase<INTSXP,NA,T>& t){
	return sugar::Sum<INTSXP,NA,T>( t ) ;
}

template <bool NA, typename T>
inline sugar::Sum<REALSXP,NA,T> sum( const VectorBase<REALSXP,NA,T>& t){
	return sugar::Sum<REALSXP,NA,T>( t ) ;
}

template <bool NA, typename T>
inline sugar::Sum<LGLSXP,NA,T> sum( const VectorBase<LGLSXP,NA,T>& t){
	return sugar::Sum<LGLSXP,NA,T>( t ) ;
}

} // Rcpp
#endif

