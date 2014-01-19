#ifndef RCPP_SUGAR_LOGICAL_IS_H
#define RCPP_SUGAR_LOGICAL_IS_H

namespace Rcpp{

	template <bool NA, typename T>
	inline bool is_true( const Rcpp::sugar::SingleLogicalResult<NA,T>& x){
		return const_cast< Rcpp::sugar::SingleLogicalResult<NA,T>& >(x).is_true() ;
	}

	template <bool NA, typename T>
	inline bool is_false( const Rcpp::sugar::SingleLogicalResult<NA,T>& x){
		return const_cast< Rcpp::sugar::SingleLogicalResult<NA,T>& >(x).is_false() ;
	}

	template <bool NA, typename T>
	inline bool is_na( const Rcpp::sugar::SingleLogicalResult<NA,T>& x){
		return const_cast< Rcpp::sugar::SingleLogicalResult<NA,T>& >(x).is_na() ;
	}
	
	
}
#endif
