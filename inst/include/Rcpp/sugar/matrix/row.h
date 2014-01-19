#ifndef Rcpp__sugar__row_h
#define Rcpp__sugar__row_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool LHS_NA, typename LHS_T>
class Row : public MatrixBase< 
	INTSXP , 
	false ,
	Row<RTYPE,LHS_NA,LHS_T>
> {
public:
	typedef Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
	
	Row( const LHS_TYPE& lhs) : nr( lhs.nrow() ), nc( lhs.ncol() ) {}
	
	inline int operator()( int i, int j ) const {
		return i + 1 ;
	}
	
	inline int size() const { return nr * nc ; }
	inline int nrow() const { return nr; }
	inline int ncol() const { return nc; }
	         
private:
	int nr, nc ;
} ;
	
} // sugar

template <int RTYPE, bool LHS_NA, typename LHS_T>
inline sugar::Row<RTYPE,LHS_NA,LHS_T>
row( const Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T>& lhs){
	return sugar::Row<RTYPE,LHS_NA,LHS_T>( lhs ) ;
}

} // Rcpp

#endif
