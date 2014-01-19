#ifndef Rcpp__sugar__all_h
#define Rcpp__sugar__all_h

namespace Rcpp{
namespace sugar{

template <bool NA, typename T>
class All : public SingleLogicalResult< true, All<NA,T> >{
public:
	typedef typename Rcpp::VectorBase<LGLSXP,NA,T> VEC_TYPE ;
	typedef SingleLogicalResult< true, All<NA,T> > PARENT ;
	All( const VEC_TYPE& t ) : PARENT() , object(t) {}
	
	void apply(){
		int n = object.size() ;
		int current = 0 ;
		PARENT::reset() ;
		for( int i=0 ; i<n ; i++){
			current = object[i] ;
			if( current == FALSE ) {
				PARENT::set_false() ; 
				return ;
			}
			if( Rcpp::traits::is_na<LGLSXP>(current)  ) {
				PARENT::set_na();
			}
		}
		if( PARENT::is_unresolved() ){
			PARENT::set_true() ;
		}
	}	
private:		
	const VEC_TYPE& object ;

} ;


template <typename T>
class All<false,T> : public SingleLogicalResult< false, All<false,T> >{
public:
	typedef typename Rcpp::VectorBase<LGLSXP,false,T> VEC_TYPE ;
	typedef SingleLogicalResult< false, All<false,T> > PARENT ;
	All( const VEC_TYPE& t ) : PARENT() , object(t) {}
	
	void apply(){
		int n = object.size() ;
		PARENT::set_true() ;
		for( int i=0 ; i<n ; i++){
			if( object[i] == FALSE ) {
				PARENT::set_false() ; 
				return ;
			}
		}
	}	
private:		
	const VEC_TYPE& object ;
} ;


} // sugar

template <bool NA, typename T>
inline sugar::All<NA,T> all( const Rcpp::VectorBase<LGLSXP,NA,T>& t){
	return sugar::All<NA,T>( t ) ;
}

} // Rcpp
#endif

