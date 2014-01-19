#ifndef Rcpp__sugar__any_h
#define Rcpp__sugar__any_h

namespace Rcpp{
namespace sugar{

template <bool NA, typename T>
class Any : public SingleLogicalResult< true, Any<NA,T> >{
public:
	typedef Rcpp::VectorBase<LGLSXP,NA,T> VEC_TYPE ;
	typedef SingleLogicalResult< true , Any<NA,T> > PARENT ;
	Any( const VEC_TYPE& t ) : PARENT() , object(t) {}
	
	void apply(){
		int n = object.size() ;
		int current = 0 ;
		PARENT::reset() ;
		for( int i=0 ; i<n ; i++){
			current = object[i] ;
			if( current == TRUE ) {
				PARENT::set_true() ; 
				return ;
			}
			if( Rcpp::traits::is_na<LGLSXP>(current)  ) {
				PARENT::set_na();
			}
		}
		if( PARENT::is_unresolved() ){
			PARENT::set_false() ;
		}
	}	
private:		
	const VEC_TYPE& object ;
} ;

template <typename T>
class Any<false,T> : public SingleLogicalResult< false, Any<false,T> >{
public:
	typedef Rcpp::VectorBase<LGLSXP,false,T> VEC_TYPE ;
	typedef SingleLogicalResult< false , Any<false,T> > PARENT ;
	Any( const VEC_TYPE& t ) : PARENT() , object(t) {}
	
	void apply(){
		int n = object.size() ;
		PARENT::set_false() ;
		for( int i=0 ; i<n ; i++){
			if( object[i] == TRUE ) {
				PARENT::set_true() ; 
				return ;
			}
		}
	}	
private:		
	const VEC_TYPE& object ;
} ;

} // sugar

template <bool NA, typename T>
inline sugar::Any<NA,T> any( const Rcpp::VectorBase<LGLSXP,NA,T>& t){
	return sugar::Any<NA,T>( t ) ;
}

} // Rcpp
#endif

