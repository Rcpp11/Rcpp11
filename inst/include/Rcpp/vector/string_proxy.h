#ifndef Rcpp__vector__string_proxy_h
#define Rcpp__vector__string_proxy_h
        
namespace Rcpp{
namespace internal{
	
	template<int RTYPE> class string_proxy {
	public:
		
		typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
		
		string_proxy() : parent(0), index(-1){};
		
		/**
		 * Creates a proxy
		 *
		 * @param v reference to the associated character vector
		 * @param index index 
		 */
		string_proxy( VECTOR& v, int index_ ) : 
			parent(&v), index(index_){
				RCPP_DEBUG( "string_proxy( VECTOR& = <%p>, index_ = %d) ", v.get__(), index_ ) ;
		}
			
		string_proxy( const string_proxy& other ) : 
			parent(other.parent), index(other.index){} ;
		
		/**
		 * lhs use. Assign the value of the referred element to 
		 * the current content of the element referred by the 
		 * rhs proxy
		 *
		 * @param rhs another proxy, possibly from another vector
		 */
		string_proxy& operator=(const string_proxy& other){
			set( other.get() ) ;
			return *this ;
		}
		
		string_proxy& operator=( const const_string_proxy<RTYPE>& other) ;
		string_proxy& operator=( const String& s) ;
		
		/**
		 * lhs use. Assigns the value of the referred element
		 * of the character vector
		 *
		 * @param rhs new content for the element referred by this proxy
		 */
		template <typename T>
		string_proxy& operator=(const std::basic_string<T>& rhs){
			set( rhs ) ;
			return *this ;
		}
		
		string_proxy& operator=(const char* rhs){
			set( Rf_mkChar( rhs ) ) ;
			return *this ;	
		}
		
		string_proxy& operator=(const wchar_t* rhs){
			set( internal::make_charsexp( rhs ) ) ;
			return *this ;	
		}
		
		
		string_proxy& operator=(SEXP rhs){
			set( rhs ) ;
			return *this ;
		}
		
		void import( const string_proxy& other){
			parent = other.parent ;
			index  = other.index ;
		}
		
    /**
     * lhs use. Adds the content of the rhs proxy to the 
     * element this proxy refers to.
     */
    template <typename T>
    string_proxy& operator+=(const T& rhs) ;
		
		/**
		 * rhs use. Retrieves the current value of the 
		 * element this proxy refers to.
		 */
		operator SEXP() const {
			return get() ;
		}
		
		/**
		 * rhs use. Retrieves the current value of the 
		 * element this proxy refers to and convert it to a 
		 * C string
		 */
		operator /* const */ char*() const {
		    return const_cast<char*>( CHAR(get()) );
		}
		 
		 
		/**
		 * Prints the element this proxy refers to to an 
		 * output stream
		 */
		template <int RT>
		friend std::ostream& operator<<(std::ostream& os, const string_proxy<RT>& proxy);
		
		template <int RT>
		friend std::string operator+( const std::string& x, const string_proxy<RT>& proxy);
		
		void swap( string_proxy& other ){
			SEXP tmp = STRING_ELT(*parent, index) ;
			SET_STRING_ELT( *parent, index, STRING_ELT( *(other.parent), other.index) ) ;
			SET_STRING_ELT( *(other.parent), other.index, tmp ) ;
		}
		
		VECTOR* parent; 
		int index ;
		inline void move( int n ){ index += n ;}
		
		inline SEXP get() const {
			return STRING_ELT( *parent, index ) ;
		}
		template <typename T>
		inline void set( const T& x ){
			set( internal::make_charsexp(x) ) ;
		}
		inline void set(SEXP x){
			SET_STRING_ELT( *parent, index, x ) ;
		}
		
		inline int size() const { return strlen( begin() ) ; }
		bool operator==( const char* other){
			return strcmp( begin(), other ) == 0 ;
		}
		bool operator!=( const char* other){
			return strcmp( begin(), other ) != 0 ;
		}
		
		bool operator==( const string_proxy& other){
			return strcmp( begin(), other.begin() ) == 0 ;
		}
		bool operator!=( const string_proxy& other){
			return strcmp( begin(), other.begin() ) != 0 ;
		}
		
		
		private:
		    typedef const char* iterator ;
		    typedef const char& reference ;
		
		    inline iterator begin() const { return CHAR( STRING_ELT( *parent, index ) ) ; }
		    inline iterator end() const { return begin() + size() ; }
		
			static std::string buffer ;
		
	} ;
	
	template <int RT>
	bool operator<( const string_proxy<RT>& lhs, const string_proxy<RT>& rhs) {
		return strcmp( 
			const_cast<char *>(lhs.begin() ), 
			const_cast<char *>(rhs.begin())
			) < 0 ;
	}

	template <int RT>
	bool operator>( const string_proxy<RT>& lhs, const string_proxy<RT>& rhs) {
		return strcmp( 
			const_cast<char *>(lhs.begin() ), 
			const_cast<char *>(rhs.begin())
			) > 0 ;
	}
	
	template <int RT>
	bool operator>=( const string_proxy<RT>& lhs, const string_proxy<RT>& rhs) {
		return strcmp( 
			const_cast<char *>(lhs.begin() ), 
			const_cast<char *>(rhs.begin())
			) >= 0 ;
	}
	
	template <int RT>
	bool operator<=( const string_proxy<RT>& lhs, const string_proxy<RT>& rhs) {
		return strcmp( 
			const_cast<char *>(lhs.begin() ), 
			const_cast<char *>(rhs.begin())
			) <= 0 ;
	}
		
	template<int RTYPE> std::string string_proxy<RTYPE>::buffer ;
	
	inline std::ostream& operator<<(std::ostream& os, const string_proxy<STRSXP>& proxy) {
	    os << static_cast<const char*>(proxy) ;
	    return os;
	}
	
	inline std::string operator+( const std::string& x, const string_proxy<STRSXP>& y ){
		return x + static_cast<const char*>(y) ;
	}
		
}
}

#endif
