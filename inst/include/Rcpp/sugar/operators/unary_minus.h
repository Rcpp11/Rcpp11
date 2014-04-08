#ifndef Rcpp__sugar__unary_minus_h
#define Rcpp__sugar__unary_minus_h

namespace Rcpp{
namespace sugar{

	template <int RTYPE>
	struct unary_minus_result_type{
		typedef typename traits::storage_type<RTYPE>::type type ;
		enum{ value = RTYPE } ;
	} ;
	template <>
	struct unary_minus_result_type<LGLSXP>{
		typedef traits::storage_type<INTSXP>::type type ;
		enum{ value = INTSXP } ;
	} ;


	template <int RTYPE,bool NA> 
	class unary_minus {
	public:
		typedef typename traits::storage_type<RTYPE>::type STORAGE ;
		typedef typename unary_minus_result_type<RTYPE>::type RESULT ;
		inline RESULT apply( STORAGE x ) const {
			return Rcpp::traits::is_na<RTYPE>(x) ? x : ( -x ) ;
		}
	} ;
	template <int RTYPE>
	class unary_minus<RTYPE,false> {
	public:
		typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
		typedef typename unary_minus_result_type<RTYPE>::type RESULT ;
		inline RESULT apply( STORAGE x ) const {
			return -x ;
		}
	} ;
	template <bool NA>
	class unary_minus<CPLXSXP,NA>{
	public:
		inline Rcomplex apply( Rcomplex x ) const {
			if (Rcpp::traits::is_na<CPLXSXP>( x ) ) return x; 
		
			Rcomplex cx ;
			cx.r = -x.r; 
			cx.i = -x.i ;
			return cx ;
		}
	} ;
	template <>
	class unary_minus<CPLXSXP,false>{
	public:
		inline Rcomplex apply( Rcomplex x ) const {
			Rcomplex cx ;
			cx.r = -x.r; 
			cx.i = -x.i ;
			return cx ;
		}
	} ;


	template <int RTYPE, bool NA, typename T>
	class UnaryMinus_Vector : public SugarVectorExpression< 
		unary_minus_result_type<RTYPE>::value ,
		NA, 
		UnaryMinus_Vector< unary_minus_result_type<RTYPE>::value ,NA,T> 
		> {
	public:
		typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
		typedef typename traits::storage_type<RTYPE>::type STORAGE ;
		typedef typename unary_minus_result_type<RTYPE>::type RESULT ;
		typedef unary_minus<RTYPE,NA> OPERATOR ;
	
		UnaryMinus_Vector( const VEC_TYPE& lhs_ ) : 
			lhs(lhs_), op() {}
	
		inline RESULT operator[]( int i ) const {
			return op.apply( lhs[i] ) ;
		}
	
		inline int size() const { return lhs.size() ; }
	
	private:
		const VEC_TYPE& lhs ;
		OPERATOR op ; 
	} ;

}
}

template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::UnaryMinus_Vector< RTYPE , NA , T >
operator-( 
	const Rcpp::VectorBase<RTYPE,NA,T>& x
) {
	return Rcpp::sugar::UnaryMinus_Vector<RTYPE,NA, T >( x ) ;
}


#endif
