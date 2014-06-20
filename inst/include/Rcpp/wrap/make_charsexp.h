#ifndef Rcpp_wrap_make_charsexp_h
#define Rcpp_wrap_make_charsexp_h
 
namespace Rcpp{
namespace internal{

    #define MAXELTSIZE 8192
    inline char* get_string_buffer(){
        static char buffer[MAXELTSIZE];
        return buffer ;    
    }

    inline SEXP make_charsexp__impl__wstring( const wchar_t* data ){
        char* buffer = get_string_buffer() ;
        wcstombs( buffer, data, MAXELTSIZE ) ;
        return Rf_mkChar(buffer) ;
    }
    inline SEXP make_charsexp__impl__wstring( wchar_t data ){
        wchar_t x[2] = { data, '\0' } ;
        char* buffer = get_string_buffer() ;
        wcstombs( buffer, x, MAXELTSIZE ) ;
        return Rf_mkChar(buffer) ;
    }
    inline SEXP make_charsexp__impl__wstring( const std::wstring& st ){
        return make_charsexp__impl__wstring( st.data()) ;
    }
    inline SEXP make_charsexp__impl__cstring( const char* data ){
        return Rf_mkChar( data ) ;
    }
    inline SEXP make_charsexp__impl__cstring( char data ){
        return Rf_mkCharLen( &data, 1 ) ;
    }

    inline SEXP make_charsexp__impl__cstring( const std::string& st ){
        return make_charsexp__impl__cstring( st.c_str() ) ;
    }

    template <typename T>
    inline SEXP make_charsexp__impl( const T& s, std::true_type ){
        return make_charsexp__impl__wstring(s) ;
    }

    template <typename T>
    inline SEXP make_charsexp__impl( const T& s, std::false_type ){
        return make_charsexp__impl__cstring(s) ;
    }

    template <typename T> 
    inline SEXP make_charsexp( const T& s) {
        return make_charsexp__impl<T>( s, typename Rcpp::traits::is_wide_string<T>::type() ) ;
    }
    template <>
    inline SEXP make_charsexp<Rcpp::String>( const Rcpp::String& );

}
}

#endif
