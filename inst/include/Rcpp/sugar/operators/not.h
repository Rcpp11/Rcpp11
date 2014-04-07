#ifndef Rcpp__sugar__not_h
#define Rcpp__sugar__not_h

namespace Rcpp{
namespace sugar{

	template <int RTYPE,bool NA> 
	class not_ {
	public:
		typedef typename traits::storage_type<RTYPE>::type STORAGE ;
		inline int apply( STORAGE x ) const {
			return Rcpp::traits::is_na<RTYPE>(x) ? NA_LOGICAL : (x ? FALSE : TRUE) ;
		}
	} ;
	template <int RTYPE>
	class not_<RTYPE,false> {
	public:
		typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
		inline int apply( STORAGE x ) const {
			return x ? FALSE : TRUE ;
		}
	} ;
	template <bool NA>
	class not_<REALSXP,NA>{
	public:
		inline int apply( double x ) const {
			return Rcpp::traits::is_na<REALSXP>( x ) ? NA_LOGICAL : ( (x == 0) ? FALSE : TRUE ) ;
		}
	} ;
	template <>
	class not_<REALSXP,false>{
	public:
		inline int apply( double x ) const {
			return ( x == 0.0 ? FALSE : TRUE ) ;
		}
	} ;
	template <bool NA>
	class not_<CPLXSXP,NA>{
	public:
		inline int apply( Rcomplex x ) const {
			return Rcpp::traits::is_na<CPLXSXP>( x ) ? NA_LOGICAL : ( (x.r == 0.0 & x.i == 0.0 ) ? FALSE : TRUE ) ;
		}
	} ;
	template <>
	class not_<CPLXSXP,false>{
	public:
		inline int apply( Rcomplex x ) const {
			return ((x.r == 0.0) & (x.i == 0.0) ) ? FALSE : TRUE ;
		}
	} ;
	
	

	template <int RTYPE, bool NA, typename T>
	class Not_Vector : public SugarVectorExpression<LGLSXP,NA, Not_Vector<RTYPE,NA,T> > {
	public:
		typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
		typedef typename traits::storage_type<RTYPE>::type STORAGE ;
		typedef not_<RTYPE,NA> OPERATOR ;
		
		Not_Vector( const VEC_TYPE& lhs_ ) : 
			lhs(lhs_), op() {}
		
		inline STORAGE operator[]( int i ) const {
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
inline Rcpp::sugar::Not_Vector< RTYPE , NA , T >
operator!( 
	const Rcpp::VectorBase<RTYPE,NA,T>& x
) {
	return Rcpp::sugar::Not_Vector<RTYPE,NA, T >( x ) ;
}


#endif
