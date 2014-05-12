#ifndef Rcpp__vector__const_string_proxy_h
#define Rcpp__vector__const_string_proxy_h
 
namespace Rcpp{
namespace internal{

    template <int RTYPE> 
    class const_string_proxy {
    public:
        friend class const_Proxy_Iterator<const_string_proxy> ;
    
        typedef typename Rcpp::Vector<RTYPE> VECTOR ;
    
        /**
         * Creates a proxy
         *
         * @param v reference to the associated character vector
         * @param index index 
         */
        const_string_proxy( const VECTOR& v, int index_ ) : parent(&v), index(index_) {}
        
        const_string_proxy( const const_string_proxy& other ) : parent(other.parent), index(other.index){} ;
    
        const_string_proxy& operator=( const const_string_proxy& ) = delete ; 
    
        void import( const const_string_proxy& other){
            parent = other.parent ;
            index  = other.index ;
        }
    
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
        friend std::ostream& operator<<(std::ostream& os, const const_string_proxy<RT>& proxy);
    
        template <int RT>
        friend std::string operator+( const std::string& x, const const_string_proxy<RT>& proxy);
    
        inline SEXP get() const {
            return STRING_ELT( *parent, index ) ;
        }
    
        inline int size() const { return strlen( begin() ) ; }
        bool operator==( const char* other){
            return strcmp( begin(), other ) == 0 ;
        }
        bool operator!=( const char* other){
            return strcmp( begin(), other ) != 0 ;
        }
    
        bool operator==( const const_string_proxy& other){
            return strcmp( begin(), other.begin() ) == 0 ;
        }
        bool operator!=( const const_string_proxy& other){
            return strcmp( begin(), other.begin() ) != 0 ;
        }
    
    
    private:
        const VECTOR* parent; 
        int index ;
        
        typedef const char* iterator ;
        typedef const char& reference ;
    
        inline iterator begin() const { return CHAR( STRING_ELT( *parent, index ) ) ; }
        inline iterator end() const { return begin() + size() ; }
    
    } ;

    template <int RT>
    bool operator<( const const_string_proxy<RT>& lhs, const const_string_proxy<RT>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) < 0 ;
    }

    template <int RT>
    bool operator>( const const_string_proxy<RT>& lhs, const const_string_proxy<RT>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) > 0 ;
    }

    template <int RT>
    bool operator>=( const const_string_proxy<RT>& lhs, const const_string_proxy<RT>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) >= 0 ;
    }

    template <int RT>
    bool operator<=( const const_string_proxy<RT>& lhs, const const_string_proxy<RT>& rhs) {
        return strcmp( 
            const_cast<char *>(lhs.begin() ), 
            const_cast<char *>(rhs.begin())
            ) <= 0 ;
    }
    
    inline std::ostream& operator<<(std::ostream& os, const const_string_proxy<STRSXP>& proxy) {
        os << static_cast<char*>(proxy) ;
        return os;
    }

    inline std::string operator+( const std::string& x, const const_string_proxy<STRSXP>& y ){
        return x + static_cast<const char*>(y) ;
    }
    
}
}

#endif
