#ifndef Rcpp__sugar__diff_h
#define Rcpp__sugar__diff_h

namespace Rcpp{
namespace sugar{

// NOTE: caching the previous value so that we only have to fetch the 
//       value once only works because we process the object from left to 
//       right
template <int RTYPE, bool LHS_NA, typename LHS_T>
class Diff : public Rcpp::VectorBase< RTYPE, LHS_NA , Diff<RTYPE,LHS_NA,LHS_T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Diff( const LHS_TYPE& lhs_ ) : 
	    lhs(lhs_), 
	    previous(lhs_[0]),
	    previous_index(0),
	    was_na(traits::is_na<RTYPE>(previous)) 
	{}
	
	inline STORAGE operator[]( int i ) const {
        STORAGE y = lhs[i+1] ;
        if( previous_index != i ){
            // we don't know the previous value, we need to get it. 
            set_previous(i, lhs[i] ) ; // record the current value
        }
        if( was_na || traits::is_na<RTYPE>(y) ) {
            set_previous(i+1, y ) ;
            return traits::get_na<RTYPE>() ; // NA
        }
        STORAGE res = y - previous ;
        set_previous( i+1, y) ;
        return res ;
	}     
	
	inline void set_previous(int i, STORAGE value) const {
	    previous = value ;
	    was_na = traits::is_na<RTYPE>(previous) ;
	    previous_index = i ;
	}
	
	inline int size() const { return lhs.size() - 1 ; }
	         
private:
	const LHS_TYPE& lhs ;
	mutable STORAGE previous ;
	mutable int previous_index ;
	mutable bool was_na ;
} ;

template <typename LHS_T, bool LHS_NA>
class Diff<REALSXP, LHS_NA, LHS_T> : public Rcpp::VectorBase< REALSXP, LHS_NA, Diff<REALSXP,LHS_NA,LHS_T> >{
public:
	typedef typename Rcpp::VectorBase<REALSXP,LHS_NA,LHS_T> LHS_TYPE ;
	
	Diff( const LHS_TYPE& lhs_ ) : lhs(lhs_), previous(lhs_[0]), previous_index(0) {}
	
	inline double operator[]( int i ) const {
		double y = lhs[i+1] ;
		if( previous_index != i ) previous = lhs[i] ;
		double res = y - previous ;
		previous = y ;
		previous_index = i+1 ;
		return res ;
	}
	inline int size() const { return lhs.size() - 1 ; }
	         
private:
	const LHS_TYPE& lhs ;
	mutable double previous ;
	mutable int previous_index ;
} ;

template <int RTYPE, typename LHS_T>
class Diff<RTYPE,false,LHS_T> : public Rcpp::VectorBase< RTYPE, false , Diff<RTYPE,false,LHS_T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,false,LHS_T> LHS_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	
	Diff( const LHS_TYPE& lhs_ ) : lhs(lhs_), previous(lhs[0]), previous_index(0) {}
	
	inline STORAGE operator[]( int i ) const {
		STORAGE y = lhs[i+1] ;
		if( previous_index != i ) previous = lhs[i] ;
		STORAGE diff = y - previous ;
		previous = y ;
		previous_index = i+1 ;
		return y - previous ;
	}
	inline int size() const { return lhs.size() - 1 ; }
	         
private:
	const LHS_TYPE& lhs ;
	mutable STORAGE previous ;
	mutable int previous_index ;
} ;

} // sugar

template <bool LHS_NA, typename LHS_T>
inline sugar::Diff<INTSXP,LHS_NA,LHS_T> diff( 
	const VectorBase<INTSXP,LHS_NA,LHS_T>& lhs
	){
	return sugar::Diff<INTSXP,LHS_NA,LHS_T>( lhs ) ;
}

template <bool LHS_NA, typename LHS_T>
inline sugar::Diff<REALSXP,LHS_NA,LHS_T> diff( 
	const VectorBase<REALSXP,LHS_NA,LHS_T>& lhs
	){
	return sugar::Diff<REALSXP,LHS_NA,LHS_T>( lhs ) ;
}

} // Rcpp
#endif

