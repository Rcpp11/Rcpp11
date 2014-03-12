#ifndef Rcpp__sugar__SingleLogicalResult_h
#define Rcpp__sugar__SingleLogicalResult_h

namespace Rcpp{
namespace sugar{  

template <bool NA,typename T>
class SingleLogicalResult {
public:
	const static int UNRESOLVED = -5 ;
	
	SingleLogicalResult() : result(UNRESOLVED) {}
	
	void apply(){
		if( result == UNRESOLVED ){
			static_cast<T&>(*this).apply() ;
		}
	}
	
	inline bool is_true(){
		apply() ;
		return result == TRUE ;
	}
	
	inline bool is_false(){
		apply() ;
		return result == FALSE ;
	}
	
	inline bool is_na(){
		apply() ;
		return Rcpp::traits::is_na<LGLSXP>( result ) ;
	}
	
	inline operator SEXP(){
		return get_sexp() ;
	}
	
	inline operator bool(){
	    static_assert( !NA, "conversion to bool is forbidden" );
		return is_true() ;
	}
	
	inline int size(){ return 1 ; }
	
	inline int get(){
		apply();
		return result;
	}
	
	inline SEXP get_sexp(){
	    apply() ;
	    return Rf_ScalarLogical( result ) ;
	}
	
protected:
	int result ;
	inline void set(int x){ result = x ;}
	inline void reset(){ set(UNRESOLVED) ; }
	inline void set_true(){ set(TRUE); }
	inline void set_false(){ set(FALSE); }
	inline void set_na(){ set(NA_LOGICAL); }
	inline bool is_unresolved(){ return result == UNRESOLVED ; }
} ;

}
}



#endif
