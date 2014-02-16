#ifndef Rcpp__vector__generic_const_name_proxy_h
#define Rcpp__vector__generic_const_name_proxy_h



namespace Rcpp{
namespace internal{
		
	template <int RTYPE> class generic_const_name_proxy {
	public:
		typedef ::Rcpp::Vector<RTYPE> VECTOR ;
		generic_const_name_proxy( const VECTOR& v, std::string  name_) :
			parent(v), name(std::move(name_)){
				RCPP_DEBUG( "generic_const_name_proxy( VECTOR& = %p, const string& = %s)", v.get__(), name_.c_str() );
		}
		generic_const_name_proxy( const generic_const_name_proxy& other ) : 
			parent(other.parent), name(other.name){}
		~generic_const_name_proxy(){}
		
		generic_const_name_proxy& operator=( const generic_const_name_proxy& other) = delete ;
		
		operator SEXP() const {
			 return get() ;
		}
		
		template <typename T>
		operator T() const {
			return ::Rcpp::as<T>( get() ) ;
		}
		
		operator bool() const{
		    return ::Rcpp::as<bool>(get()); 
		}
		
	private:
		const VECTOR& parent ;
		std::string name;
		
		SEXP get() const {
			return parent[ parent.offset(name) ];
		}
		
	} ;
}
}
#endif
