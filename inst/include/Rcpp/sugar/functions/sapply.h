#ifndef Rcpp__sugar__sapply_h
#define Rcpp__sugar__sapply_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T, typename Function, bool NO_CONVERSION>
class Sapply : public SugarVectorExpression< 
	Rcpp::traits::r_sexptype_traits<
		typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type
	>::rtype , 
	true ,
	Sapply<RTYPE,NA,T,Function,NO_CONVERSION>
> {
public:
	typedef typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type result_type ; 
	
	const static int RESULT_R_TYPE = 
		Rcpp::traits::r_sexptype_traits<result_type>::rtype ;
	
	typedef Rcpp::VectorBase<RTYPE,NA,T> VEC ;
	typedef typename Rcpp::traits::r_vector_element_converter<RESULT_R_TYPE>::type converter_type ;
	typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type STORAGE ;
	
	typedef typename Rcpp::traits::Extractor< RTYPE, NA, T>::type EXT ;
	
	Sapply( const VEC& vec_, Function fun_ ) : vec(vec_.get_ref()), fun(fun_){
	    RCPP_DEBUG( "Sapply With Converter = %s", DEMANGLE(Sapply) )
	    RCPP_DEBUG( "Sapply Converter = %s", DEMANGLE(converter_type) ) 
	}
	
	inline STORAGE operator[]( int i ) const {
		STORAGE res = converter_type::get( fun( vec[i] ) );
		return res ;
	}
	inline int size() const { return vec.size() ; }
	         
private:
	const EXT& vec ;
	Function fun ;
	
} ;


template <int RTYPE, bool NA, typename T, typename Function>
class Sapply<RTYPE,NA,T,Function,true> : public SugarVectorExpression< 
	Rcpp::traits::r_sexptype_traits<
		typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type
	>::rtype , 
	true ,
	Sapply<RTYPE,NA,T,Function,true>
> {
public:
	typedef typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type result_type ; 
	const static int RESULT_R_TYPE = 
		Rcpp::traits::r_sexptype_traits<result_type>::rtype ;
	
	typedef Rcpp::VectorBase<RTYPE,NA,T> VEC ;
	typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type STORAGE ;
	
	typedef typename Rcpp::traits::Extractor< RTYPE, NA, T>::type EXT ;
	
	Sapply( const VEC& vec_, Function fun_ ) : vec(vec_.get_ref()), fun(fun_){
	    RCPP_DEBUG( "Sapply  = %s", DEMANGLE(Sapply) )
	}
	
	inline STORAGE operator[]( int i ) const {
		return fun( vec[i] ) ;
	}
	inline int size() const { return vec.size() ; }
	         
private:
	const EXT& vec ;
	Function fun ;
	
} ;
	

} // sugar

template <int RTYPE, bool NA, typename T, typename Function >
inline sugar::Sapply<
    RTYPE,NA,T,Function, 
    std::is_same< 
        typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type )>::type ,  
        typename Rcpp::traits::storage_type< traits::r_sexptype_traits< typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type >::rtype >::type
    >::value
> 
sapply( const Rcpp::VectorBase<RTYPE,NA,T>& t, Function fun ){
    typedef typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type result_type ; 
	return sugar::Sapply<RTYPE,NA,T,Function, 
	std::is_same< 
        result_type,  
        typename Rcpp::traits::storage_type< traits::r_sexptype_traits<result_type>::rtype >::type
    >::value >( t, fun ) ;
}

} // Rcpp

#endif
