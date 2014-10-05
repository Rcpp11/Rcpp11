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
        String( ): data( Rf_mkChar("") ){}

        /** copy constructor */
        String( const String& other) : data( other.data ){}

        /** construct a string from a single CHARSXP SEXP */
        String(SEXP charsxp) : data(charsxp){}

        /** from string proxy */
        template <typename Vec>
        String( const internal::string_proxy<Vec>& proxy ): data( proxy.get() ){}

        /** from a std::string */
        String( std::string s) : data( internal::make_charsexp(s) ){}

        String( const std::wstring& s) : data( internal::make_charsexp(s) ){}

        /** from a const char* */
        String( const char* s) : data( internal::make_charsexp(s) ){}

        String( const wchar_t* s) : data(internal::make_charsexp(s)){}

        /** constructors from R primitives */
        String( int x ) : data( internal::r_coerce<INTSXP,STRSXP>(x) ){}
        String( double x ) : data( internal::r_coerce<REALSXP,STRSXP>(x) ){}
        String( Rboolean x ) : data( internal::r_coerce<LGLSXP,STRSXP>(x) ){}
        String( Rcomplex x ) : data( internal::r_coerce<CPLXSXP,STRSXP>(x) ){}
        String( Rbyte x ) : data( internal::r_coerce<RAWSXP,STRSXP>(x) ){}
        String( Na_Proxy ) ;

        inline String& operator=( int x     ){ 
            data = internal::r_coerce<INTSXP ,STRSXP>( x ) ; 
            return *this ; 
        }
        inline String& operator=( double x  ){ 
            data = internal::r_coerce<REALSXP,STRSXP>( x ) ; 
            return *this ; 
        }
        inline String& operator=( Rbyte x   ){ 
            data = internal::r_coerce<RAWSXP ,STRSXP>( x ) ; 
            return *this ; 
        }
        inline String& operator=( Rboolean x ){ 
            data = internal::r_coerce<LGLSXP ,STRSXP>( x ) ; 
            return *this ; 
        }
        inline String& operator=( Rcomplex x){ 
            data = internal::r_coerce<CPLXSXP,STRSXP>( x ) ; 
            return *this ; 
        }
        inline String& operator=( SEXP x){ 
            data = x ; 
            return *this ; 
        }

        template <typename Vec>
        inline String& operator=( const internal::string_proxy<Vec>& proxy){
            data = proxy.get() ; 
            return *this ;
        }
        inline String& operator=( const String& other ){ 
            data = other.data ; 
            return *this ; 
        }
        inline String& operator=( const std::string& s){ 
            data = internal::make_charsexp(s) ;
            return *this ; 
        }
        inline String& operator=( const char* s){ 
            data = internal::make_charsexp(s) ;
            return *this ; 
        }
        inline String& operator=( const std::wstring& s){  
            data = internal::make_charsexp(s) ;
            return *this ; 
        }
        inline String& operator=( const wchar_t* s){ 
            data = internal::make_charsexp(s) ;
            return *this ; 
        }
    
        inline String& operator=( Na_Proxy ) ; 

        inline String& operator+=( const std::string& s){
            return append<std::string, std::string>(s) ; 
        }
        inline String& operator+=( const char* s){
            return append<const char*,std::string>(s) ;
        }
        inline String& operator+=( const std::wstring& s){ 
            return append<std::wstring,std::wstring>( s ); 
        }
        inline String& operator+=( const wchar_t* s){ 
            return append<const wchar_t*,std::wstring>( s ); 
        }

     private:
         
         template <typename T, typename string_type>
         inline String& append( const T& s ){
            if( !is_na() ){
                const char* raw = CHAR(data) ;
                string_type res( raw, raw + strlen(raw) ) ;
                res += s ;
                data = internal::make_charsexp(res) ;
            }
            return *this ;
         }
         
         template <typename T, typename string_type>
         inline String& prepend( const T& s ){
            if( !is_na() ){
                string_type res{s} ;
                const char* raw = CHAR(data) ;
                res.append( raw, raw + strlen(raw) ) ;
                data = internal::make_charsexp(res) ;
            }
            return *this ;
         }
         
     public:

        inline String& operator+=( const String& other ){
            if( other.is_na() ){ 
                data = NA_STRING ;
                return *this ;
            } 
            return append<const char*,std::string>( CHAR(other.data) ) ;    
        }
        template <typename Vec>
        inline String& operator+=( const internal::string_proxy<Vec>& proxy){
            return this->operator+=( String(proxy) ) ;
        }
        inline String& operator+=( SEXP x){
            return this->operator+=( String(x) ) ;
        }

        template <typename T>
        inline String& push_back( const T& s){
            return this->operator+=(s) ;
        }
        
        inline String& push_front( const char* s){
            return prepend<const char*,std::string>(s) ;
        }
        inline String& push_front( const std::string& s){
            return prepend<std::string,std::string>(s) ;
        }
        inline String& push_front( const Rcpp::String& s){
            if( s.is_na() ){
                data = NA_STRING ;
                return *this ;
            }
            return prepend<const char*, std::string>( CHAR(s.data) ) ;
        }

        inline operator SEXP() const {
            return data ;
        }
        
        // inline operator std::string() const {
        //     return get_cstring() ;
        // }
        // 
        // inline operator std::wstring() const {
        //     const char* s = get_cstring() ;
        //     return std::wstring( s, s + strlen(s) );
        // }

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
