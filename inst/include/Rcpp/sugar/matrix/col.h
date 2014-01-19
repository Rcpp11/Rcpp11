#ifndef Rcpp__sugar__col_h
#define Rcpp__sugar__col_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool LHS_NA, typename LHS_T>
class Col : public MatrixBase< 
	INTSXP , 
	false ,
	Col<RTYPE,LHS_NA,LHS_T>
> {
public:
	typedef Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
	
	Col( const LHS_TYPE& lhs) : nr( lhs.ncol() ), nc( lhs.ncol() ) {}
	
	inline int operator()( int i, int j ) const {
		return j + 1 ;
	}
	
	inline int size() const { return nr * nc ; }
	inline int nrow() const { return nr; }
	inline int ncol() const { return nc; }
	         
private:
	int nr, nc ;
} ;
	
} // sugar

template <int RTYPE, bool LHS_NA, typename LHS_T>
inline sugar::Col<RTYPE,LHS_NA,LHS_T> 
col( const Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T>& lhs){
	return sugar::Col<RTYPE,LHS_NA,LHS_T>( lhs ) ;
}

} // Rcpp

#endif
