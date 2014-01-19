#ifndef Rcpp_internal_converter_h
#define Rcpp_internal_converter_h

namespace Rcpp{
namespace internal{
	
	class converter {
	public:
		converter( ) : x(R_NilValue){}
		converter( SEXP x_) : x(x_){}
		
		template <typename T> operator T(){
			return ::Rcpp::as<T>( x ) ;	
		}
	private:
		SEXP x ;
		
	} ;
	
}
}

#endif
