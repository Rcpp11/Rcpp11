#ifndef Rcpp__vector__traits_h
#define Rcpp__vector__traits_h
 
namespace Rcpp{
namespace traits{

	template <int RTYPE>
	class r_vector_cache{
	public:
		typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
		typedef typename r_vector_iterator<RTYPE>::type iterator ;
		typedef typename r_vector_const_iterator<RTYPE>::type const_iterator ;
		typedef typename r_vector_proxy<RTYPE>::type proxy ;
		typedef typename r_vector_const_proxy<RTYPE>::type const_proxy ;
		typedef typename storage_type<RTYPE>::type storage_type ;
		
		r_vector_cache() : start(0){}
		
		inline void update( const VECTOR& v ) {
		    start = ::Rcpp::internal::r_vector_start<RTYPE>(v.get__()) ;
			RCPP_DEBUG( " cache<%d>::update( <%p> ), start = <%p>", RTYPE, reinterpret_cast<void*>(v.get__()),  reinterpret_cast<void*>(start) )
		}
		inline iterator get() const { return start; }
		inline const_iterator get_const() const { return start; }
		
		inline proxy ref() { return *start ;}
		inline proxy ref(int i) { return start[i] ; }
		
		inline const_proxy ref() const { return *start ;}
		inline const_proxy ref(int i) const { return start[i] ; }   
		
		private:
			iterator start ;
	} ;
	template <int RTYPE> class proxy_cache{
	public:
		typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
		typedef typename r_vector_iterator<RTYPE>::type iterator ;
		typedef typename r_vector_const_iterator<RTYPE>::type const_iterator ;
		typedef typename r_vector_proxy<RTYPE>::type proxy ;
		typedef typename r_vector_const_proxy<RTYPE>::type const_proxy ;
		
		proxy_cache(): p(0){}
		~proxy_cache(){}
		void update( const VECTOR& v ){
			p = const_cast<VECTOR*>(&v) ;
			RCPP_DEBUG( " cache<%d>::update( <%p> ), p = <%p>", RTYPE, reinterpret_cast<void*>(v.get__()),  reinterpret_cast<void*>(p) ) ;
		}
		inline iterator get() const { return iterator( proxy(*p, 0 ) ) ;}
		inline const_iterator get_const() const { return const_iterator( const_proxy( *p, 0 ) ) ;}
		
		inline proxy ref() { return proxy(*p,0) ; }
		inline proxy ref(int i) { return proxy(*p,i);}
		
		inline const_proxy ref() const { return const_proxy(*p,0) ; }
		inline const_proxy ref(int i) const { return const_proxy(*p,i);}
		
		private:
			VECTOR* p ;
	} ;
	
	// regular types for INTSXP, REALSXP, ...
	template <int RTYPE> struct r_vector_cache_type { typedef r_vector_cache<RTYPE> type ;  } ;
	
	// proxy types for VECSXP, STRSXP and EXPRSXP
	template <> struct r_vector_cache_type<VECSXP>  { typedef proxy_cache<VECSXP> type ;  } ;
	template <> struct r_vector_cache_type<EXPRSXP> { typedef proxy_cache<EXPRSXP> type ; } ;
	template <> struct r_vector_cache_type<STRSXP>  { typedef proxy_cache<STRSXP> type ;  } ;
		
} // traits 
}

#endif
