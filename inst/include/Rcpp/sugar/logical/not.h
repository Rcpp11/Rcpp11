#ifndef Rcpp__sugar__logical__not_h
#define Rcpp__sugar__logical__not_h

namespace Rcpp{
namespace sugar{  

template <bool NA> struct negate{
	static inline int apply( int x ){
		return Rcpp::traits::is_na<LGLSXP>( x ) ? x : 
			( x ? FALSE : TRUE ) ;
	}
} ;
template<> struct negate<false>{
	static inline int apply( int x){
		return x ? FALSE : TRUE ;
	}
} ;


template <bool NA, typename T>
class Negate_SingleLogicalResult : public SingleLogicalResult<NA, Negate_SingleLogicalResult<NA,T> >{
public:
	typedef SingleLogicalResult<NA,T> TYPE ;
	typedef SingleLogicalResult<NA, Negate_SingleLogicalResult<NA,T> > BASE ;
	Negate_SingleLogicalResult( const TYPE& orig_ ) : orig(orig_) {}
	
	inline void apply(){
		BASE::set( negate<NA>::apply( orig.get() ) );
	}
	
private:
	const TYPE& orig ;
	
} ;

}
}

template <bool NA,typename T>
inline Rcpp::sugar::Negate_SingleLogicalResult<NA,T> 
operator!( const Rcpp::sugar::SingleLogicalResult<NA,T>& x){
	return Rcpp::sugar::Negate_SingleLogicalResult<NA,T>( x );
}


#endif
