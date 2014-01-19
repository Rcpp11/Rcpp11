#ifndef Rcpp__traits__wrap_type_traits__h
#define Rcpp__traits__wrap_type_traits__h

namespace Rcpp{
namespace traits{

/**
 * primitive type : int, double, std::string, Rcomplex, size_t, Rbyte
 */
struct wrap_type_primitive_tag{};

/**
 * unknown. Implicit conversion to SEXP will be tried.
 */
struct wrap_type_unknown_tag{};
 
/**
 * declared module object type (by the RCPP_EXPOSED_CLASS macro)
 */
struct wrap_type_module_object_tag{} ;

/**
 * enums
 */
struct wrap_type_enum_tag{} ;

/**
 * Type trait that helps the dispatch of wrap to the proper method
 *
 * This builds a struct that contains a typedef called wrap_category
 * that has to be one of "wrap_type_primitive_tag" or "wrap_type_unknown_tag"
 *
 * The default is "wrap_type_unknown_tag" and this is specialized
 * for primitive types
 */
template <typename T> struct wrap_type_traits { typedef wrap_type_unknown_tag wrap_category; } ;

/**
 * Total specialization for primitive types
 */
template <> struct wrap_type_traits<int> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<const int> { typedef wrap_type_primitive_tag wrap_category; } ;

template <> struct wrap_type_traits<double> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<Rbyte> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<Rcomplex> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<unsigned int> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<bool> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<std::string> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<std::wstring> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<Rcpp::String> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<char> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<wchar_t> { typedef wrap_type_primitive_tag wrap_category; } ;

template <> struct wrap_type_traits<float> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits< std::complex<float> > { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits< std::complex<double> > { typedef wrap_type_primitive_tag wrap_category; } ;

template <> struct wrap_type_traits<long> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<unsigned long> { typedef wrap_type_primitive_tag wrap_category; } ;

template <> struct wrap_type_traits<long double> { typedef wrap_type_primitive_tag wrap_category; } ;

template <> struct wrap_type_traits<short> { typedef wrap_type_primitive_tag wrap_category; } ;
template <> struct wrap_type_traits<unsigned short> { typedef wrap_type_primitive_tag wrap_category; } ;

} // namespace traits
} // namespace Rcpp
#endif
