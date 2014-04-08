#ifndef Rcpp__vector__string_const_name_proxy_h
#define Rcpp__vector__string_const_name_proxy_h



namespace Rcpp{
namespace internal{

	template <int RTYPE>
	class string_const_name_proxy{
	public:
		typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
	
		string_const_name_proxy( const VECTOR& v, std::string  name_) :
			parent(v), name(std::move(name_)){}
		string_const_name_proxy( const string_const_name_proxy& other ) : 
			parent(other.parent), name(other.name){}
		~string_const_name_proxy(){}
	
		string_const_name_proxy& operator=( const string_const_name_proxy& other) = delete ;
	
		operator char* (){
			 return get() ;
		}
	
		operator SEXP(){
			return Rf_mkString(get()) ;
		}
	
	private:
		VECTOR& parent ;
		std::string name;
	
		char* get(){
			return parent.at(name) ;
		}
	
	} ;

}
}
#endif
