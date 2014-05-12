#ifndef Rcpp__vector__string_proxy_h
#define Rcpp__vector__string_proxy_h
        
namespace Rcpp{
namespace internal{

    template <typename Vec> 
    class string_proxy {
    public:
        friend class Proxy_Iterator<string_proxy> ;
        
        /**
         * Creates a proxy
         *
         * @param v reference to the associated character vector
         * @param index index 
         */
        string_proxy( Vec& v, int index_ ) : 
            parent(v), index(index_){}
        
        string_proxy( const string_proxy& other ) = default ;
    
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
    
        inline operator std::string() const {
            return std::string( CHAR(get()) );
        }
        
        inline operator std::string() {
            return std::string( CHAR(get()) );
        }
        
        friend inline std::ostream& operator<<(std::ostream& os, const string_proxy& proxy) {
            os << std::string(proxy) ;
            return os;
        }
        
        friend inline std::string operator+( const std::string& x, const string_proxy& y ){
            return x + std::string(y) ;
        }
    
        friend inline void swap( string_proxy<Vec>& a, string_proxy<Vec>& b){      
            SEXP tmp = STRING_ELT(a.parent, a.index) ;
            SET_STRING_ELT( a.parent, a.index, STRING_ELT( b.parent, b.index) ) ;
            SET_STRING_ELT( b.parent, b.index, tmp ) ;                                       
        }

        inline SEXP get() const {
            return STRING_ELT( parent, index ) ;
        }
        template <typename T>
        inline void set( const T& x ){
            set( internal::make_charsexp(x) ) ;
        }
        inline void set(SEXP x){
            SET_STRING_ELT( parent, index, x ) ;
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
        Vec& parent; 
        int index ;
        
        typedef const char* iterator ;
        typedef const char& reference ;
        
        inline iterator begin() const { return CHAR( STRING_ELT( parent, index ) ) ; }
        inline iterator end() const { return begin() + size() ; }
        
    } ;
    

    template <typename Vec1, typename Vec2>
    bool operator<( const string_proxy<Vec1>& lhs, const string_proxy<Vec2>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) < 0 ;
    }

    template <typename Vec1, typename Vec2>
    bool operator>( const string_proxy<Vec1>& lhs, const string_proxy<Vec2>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) > 0 ;
    }

    template <typename Vec1, typename Vec2>
    bool operator>=( const string_proxy<Vec1>& lhs, const string_proxy<Vec2>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) >= 0 ;
    }

    template <typename Vec1, typename Vec2>
    bool operator<=( const string_proxy<Vec1>& lhs, const string_proxy<Vec2>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) <= 0 ;
    }
    
}
}

#endif
