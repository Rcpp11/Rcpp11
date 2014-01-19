#ifndef Rcpp_Named_h    
#define Rcpp_Named_h
                     
namespace Rcpp{ 
                    
class Argument {
public:
	Argument() : name(){}
	Argument( const std::string& name_) : name(name_){} 
	
	template<typename T>
	inline traits::named_object<T> operator=( const T& t){
		return traits::named_object<T>( name, t ) ;	
	}
	
	std::string name ;	
} ;

inline Argument Named( const std::string& name){
	return Argument( name );	
}
template <typename T>
inline traits::named_object<T> Named( const std::string& name, const T& o){
	return traits::named_object<T>( name, o );	
}

namespace internal{

class NamedPlaceHolder {
public:
	NamedPlaceHolder(){}
	~NamedPlaceHolder(){}
	Argument operator[]( const std::string& arg) const {
		return Argument( arg ) ;
	}
	Argument operator()(const std::string& arg) const {
		return Argument( arg ) ;
	}
	operator SEXP() const { return R_MissingArg ; }
} ;
} // internal

static internal::NamedPlaceHolder _ ;

} // namespace Rcpp

#endif
