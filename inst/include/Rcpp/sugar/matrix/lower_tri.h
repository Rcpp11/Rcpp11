#ifndef Rcpp__sugar__lower_tri_h
#define Rcpp__sugar__lower_tri_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool LHS_NA, typename LHS_T>
class LowerTri : public VectorBase< 
	LGLSXP , 
	false ,
	LowerTri<RTYPE,LHS_NA,LHS_T>
> {
public:
	typedef Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
	
	LowerTri( const LHS_TYPE& lhs, bool diag) : 
		nr( lhs.nrow() ), nc( lhs.ncol() ), 
		getter( diag ? (&LowerTri::get_diag_true) : (&LowerTri::get_diag_false) ){}
	
	// inline int operator[]( int index ) const {
	// 	int i = Rcpp::internal::get_line( index, nr ) ;
	// 	int j = Rcpp::internal::get_column( index, nr, i ) ;
	// 	return get(i,j) ; 
	// }
	inline int operator()( int i, int j ) const {
		return get(i,j) ;
	}
	
	inline int size() const { return nr * nc ; }
	inline int nrow() const { return nr; }
	inline int ncol() const { return nc; }
	         
private:
	int nr, nc ;
	typedef bool (LowerTri::*Method)(int,int) ;
	
	Method getter ;
	inline bool get_diag_true( int i, int j ){
		return i <= j ;
	}
	inline bool get_diag_false( int i, int j ){
		return i < j ;
	}
	inline bool get( int i, int j){
		return (this->*getter)(i, j ) ;
	}
	
} ;
	
} // sugar

template <int RTYPE, bool LHS_NA, typename LHS_T>
inline sugar::LowerTri<RTYPE,LHS_NA,LHS_T>
lower_tri( const Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T>& lhs, bool diag = false){
	return sugar::LowerTri<RTYPE,LHS_NA,LHS_T>( lhs, diag ) ;
}

} // Rcpp

#endif
