#ifndef Rcpp__traits__is_wide_string__h
#define Rcpp__traits__is_wide_string__h

namespace Rcpp{
namespace traits{

    template <typename T>
    struct is_wide_string : public std::is_same< typename T::value_type, wchar_t > {} ;
	
    template <> struct is_wide_string< const wchar_t* > : public std::true_type{} ;
    template <> struct is_wide_string< const char* > : public std::false_type{} ;
    
    template <> struct is_wide_string< wchar_t > : public std::true_type{} ;
    template <> struct is_wide_string< char > : public std::false_type{} ;
    
} // traits
} // Rcpp

#endif
