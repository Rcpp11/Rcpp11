#ifndef RCPP_SUGAR_SUGARMATH_H
#define RCPP_SUGAR_SUGARMATH_H

namespace Rcpp{
namespace sugar{
	
template <bool NA, typename OUT, typename U1, typename T1, typename FunPtr>
class SugarMath_1 : public Rcpp::VectorBase< 
	Rcpp::traits::r_sexptype_traits<OUT>::rtype , 
	NA, 
	SugarMath_1<NA,OUT,U1,T1,FunPtr>
	> {
public:
	
	typedef Rcpp::VectorBase< Rcpp::traits::r_sexptype_traits<OUT>::rtype ,NA,T1> VEC_TYPE ;
	
	SugarMath_1( FunPtr ptr_, const VEC_TYPE & vec_) : ptr(ptr_), vec(vec_){}
	
	inline OUT operator[]( int i) const { 
		U1 x = vec[i] ;
		if( ISNAN(x) ) return x;
		return ptr( x ) ;
	}
	inline int size() const { return vec.size() ; }
	
private:
	FunPtr ptr ;
	const VEC_TYPE& vec ;
};

template <bool NA, typename OUT, typename T1, typename FunPtr>
class SugarMath_1<NA,OUT,int,T1,FunPtr> : public Rcpp::VectorBase< 
	Rcpp::traits::r_sexptype_traits<OUT>::rtype , 
	NA, 
	SugarMath_1<NA,OUT,int,T1,FunPtr>
	> {
public:
	typedef Rcpp::VectorBase< INTSXP ,NA,T1> VEC_TYPE ;
	
	SugarMath_1( FunPtr ptr_, const VEC_TYPE & vec_) : ptr(ptr_), vec(vec_){}
	
	inline OUT operator[]( int i) const { 
		int x = vec[i] ;
		if( Rcpp::traits::is_na<INTSXP>(x) ) return Rcpp::traits::get_na<REALSXP>( ) ;
		return ptr( x ) ;
	}
	inline int size() const { return vec.size() ; }
	
private:
	FunPtr ptr ;
	const VEC_TYPE& vec ;
};

template <typename OUT, typename T1, typename FunPtr>
class SugarMath_1<false,OUT,int,T1,FunPtr> : public 
Rcpp::VectorBase< 
	Rcpp::traits::r_sexptype_traits<OUT>::rtype , 
	false, 
	SugarMath_1<false,OUT,int,T1,FunPtr>
> {
public:
	typedef Rcpp::VectorBase< INTSXP ,false,T1> VEC_TYPE ;
	SugarMath_1( FunPtr ptr_, const VEC_TYPE & vec_) : ptr(ptr_), vec(vec_){}
	
	inline OUT operator[]( int i) const { 
		return ptr( vec[i] ) ;
	}
	inline int size() const { return vec.size() ; }
	
private:
	FunPtr ptr ;
	const VEC_TYPE& vec ;
};


} // sugar
} // Rcpp

#define SUGAR_MATH_1(__NAME__,__SYMBOL__)                                    \
	namespace Rcpp{                                                          \
	template <bool NA, typename T>                                           \
	inline sugar::SugarMath_1<NA,double,double,T, double (*)(double) >       \
	__NAME__(                                                                \
		const VectorBase<REALSXP,NA,T>& t                                    \
	){                                                                       \
		return sugar::SugarMath_1<NA,double,double,T, double (*)(double)>(   \
			&__SYMBOL__ , t                                                   \
		) ;                                                                  \
	}                                                                        \
	inline sugar::SugarMath_1<true,double,double,NumericVector,double(*)(double)>   \
	__NAME__( SEXP x){ return __NAME__( NumericVector( x ) ) ; }             \
	template <bool NA, typename T>                                           \
	inline sugar::SugarMath_1<NA,double,int,T, double (*)(double) >          \
	__NAME__(                                                                \
		const VectorBase<INTSXP,NA,T>& t                                     \
	){                                                                       \
		return sugar::SugarMath_1<NA,double,int,T, double (*)(double)>(      \
			&__SYMBOL__ , t                                                   \
		) ;                                                                  \
	}                                                                        \
	}

#endif
