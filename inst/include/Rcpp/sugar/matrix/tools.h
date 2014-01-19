#ifndef RCPP_SUGAR_MATRIX_TOOLS_H
#define RCPP_SUGAR_MATRIX_TOOLS_H

namespace Rcpp{
namespace internal{

	inline int get_line( int index, int nr ){
		return index % nr ;
	}

	inline int get_column( int index, int nr ){
		int i = get_line( index, nr ); 
		return (index-i) / nr ;
	}
	
	inline int get_column( int index, int nr, int i ){
		return (index-i) / nr ;
	}

}
}

#endif
