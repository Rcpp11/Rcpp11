#ifndef Rcpp__String_h
#define Rcpp__String_h

namespace Rcpp {

    /**
     * A single string, i.e. an element of a character vector.
     * This represents CHARSXP SEXP
     */
    class String {
    public:

        /** default constructor */
        String(): data( Rf_mkChar("") ){}

        /** copy constructor */
        String( const String& other) = default ;
        String( String&& other ) = default ;
        inline String& operator=( const String& other ) = default ;
        inline String& operator=( String&& other ) = default ;
        ~String() = default ;
        
        /** construct a string from a single CHARSXP SEXP */
        String(SEXP charsxp) {
            if( TYPEOF(charsxp) != CHARSXP ) stop( "expecting a CHARSXP, got: %s", type2name(charsxp) ) ;
            data = Rf_mkCharCE(Rf_translateCharUTF8(charsxp), CE_UTF8) ;
        }

        /** from string proxy */
        template <typename Vec>
        String( const internal::string_proxy<Vec>& proxy ): String( proxy.get() ){}

        /** from a const char* */
        String( const char* s) : data( Rf_mkCharCE(s, CE_UTF8) ){}

        /** from a std::string */
        String( std::string s) : String(s.c_str()) {}

        String( const wchar_t* s) : data(internal::make_charsexp(s)){}
        String( const std::wstring& s) : String(s.c_str()){}

        /** constructors from R primitives */
        String( int x ) : data( internal::r_coerce<INTSXP,STRSXP>(x) ){}
        String( double x ) : data( internal::r_coerce<REALSXP,STRSXP>(x) ){}
        String( Rboolean x ) : data( internal::r_coerce<LGLSXP,STRSXP>(x) ){}
        String( Rcomplex x ) : data( internal::r_coerce<CPLXSXP,STRSXP>(x) ){}
        String( Rbyte x ) : data( internal::r_coerce<RAWSXP,STRSXP>(x) ){}
        String( Na_Proxy ) ;
                
        template <typename T>
        inline String& operator=( T&& x){
            data = String(std::forward<T>(x)).data ;
            return *this ;
        }
        
        inline String& operator=( Na_Proxy ) ; 

        template <typename T>
        inline String& operator+=( T&& s ){
            return append(std::forward<T>(s)) ;    
        }
        
        template <typename T>
        inline String& push_back( T&& s){
            return append(std::forward<T>(s)) ;
        }
        
        template <typename T>
        inline String& push_front( T&& s){
            return prepend(std::forward<T>(s)) ;
        }
        
        inline operator SEXP() const {
            return data ;
        }
        
        inline const char* get_cstring() const {
            return CHAR(data) ;
        }

        bool operator<( const Rcpp::String& other ) const {
            return strcmp( get_cstring(), other.get_cstring() ) < 0;
        }

        bool operator==( const Rcpp::String& other) const {
            return data == other.data ;
        }
        bool operator!=( const Rcpp::String& other) const {
            return data != other.data ;
        }

        bool operator>( const Rcpp::String& other ) const {
            return strcmp( get_cstring(), other.get_cstring() ) > 0;
        }

    private:

        /** the CHARSXP this String encapsulates */
        SEXP data ;

        inline bool is_na() const { 
            return data == NA_STRING ; 
        }
        
        template <typename T>
        inline String& append( T&& other ){
            if( is_na() ) return *this ;
            String s{ other} ;
            if( s.is_na() ){
               data = NA_STRING ;
            } else {     
               const char* raw = CHAR(data) ;
               std::string res( raw, raw + strlen(raw) ) ;
               res += CHAR(s.data) ;
               data = internal::make_charsexp(res) ;
            }
            return *this ;
        }
        
        template <typename T>
        inline String& prepend( T&& other){
            String s{other} ;
            s += *this ;
            data = s.data ;
            return *this ;
        }

    } ;

    namespace traits{
        template<> struct r_type_traits<Rcpp::String>{ typedef r_type_string_tag r_category ; } ;
        template<> struct r_sexptype_traits<Rcpp::String>{ enum{ rtype = STRSXP } ; } ;
    }

    namespace internal {

        template <typename Vec>
        template <typename T>
        inline void string_proxy<Vec>::set( const T& x ) {
            set( (SEXP)String(x) ) ;
        }
        
        template <typename T>
        inline SEXP string_element_converter::get__impl( const T& input, std::true_type){
            return String(input.object) ;
        }
        
        template <typename T>
        inline SEXP string_element_converter::get__impl( const T& input, std::false_type){
            return String(input) ;
        }
    
        template <typename Vec>
        template <typename T>
        string_proxy<Vec>& string_proxy<Vec>::operator+=(const T& rhs) {
            String tmp = get() ;
            tmp += rhs ;
            set( tmp ) ;
            return *this ;
        }

        template<> inline SEXP caster<String,SEXP>( String from ) {
            return from ;
        }

    }
    
    template <> struct Wrapper<String>{
        inline static SEXP wrap( const String& s ){
            return CharacterVector{ s } ;    
        }
    } ;

} // Rcpp

namespace std {
    template <> struct hash<Rcpp::String>{
        inline size_t operator()(const Rcpp::String& s) const noexcept {
            return std::hash<SEXP>()(s) ;
        }
    } ;
}

#endif
