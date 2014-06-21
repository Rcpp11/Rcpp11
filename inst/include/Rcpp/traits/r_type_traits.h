#ifndef Rcpp__traits__r_type_traits__h
#define Rcpp__traits__r_type_traits__h

namespace Rcpp{
namespace traits{

/**
 * Identifies a primitive type that needs no special handling
 * int, double, Rbyte, Rcomplex
 */
struct r_type_primitive_tag{} ;

/**
 * Identifies that the associated type can be implicitely converted
 * to std::string
 */
struct r_type_string_tag{} ;

/**
 * Default
 */
struct r_type_generic_tag{} ;

/**
 * Identifies a pair<const KEY, VALUE>, used to wrap map<KEY, VALUE>
 * VALUE can be anything that wraps, KEY can be anything we can build a String from
 */
struct r_type_pair_tag{} ;

/**
 * identifies an enum. conversions from/to int is used
 */ 
struct r_type_enum_tag{} ;

/**
 * R type trait. Helps wrap.
 */
template <typename T> struct r_type_traits { 
    typedef typename std::conditional<
        std::is_enum<T>::value,
        r_type_enum_tag,
        r_type_generic_tag
    >::type r_category ; 
} ;

template <typename KEY, typename VALUE> 
struct r_type_traits< std::pair<const KEY,VALUE> > { 
    typedef r_type_pair_tag r_category ; 
} ;

template<> struct r_type_traits<int>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<const int>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<double>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<const double>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<Rbyte>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<Rcomplex>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<bool>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<std::string>{ typedef r_type_string_tag r_category ; } ;
template<> struct r_type_traits<std::wstring>{ typedef r_type_string_tag r_category ; } ;
template<> struct r_type_traits<char>{ typedef r_type_string_tag r_category ; } ;
template<> struct r_type_traits<wchar_t>{ typedef r_type_string_tag r_category ; } ;

template<> struct r_type_traits<unsigned int>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<float>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<const char*>{ typedef r_type_string_tag r_category ; } ;
template<> struct r_type_traits<const wchar_t*>{ typedef r_type_string_tag r_category ; } ;

template<> struct r_type_traits<long>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<unsigned long>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<long double>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<short>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits<unsigned short>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::complex<double> >{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::complex<float> >{ typedef r_type_primitive_tag r_category ; } ;

} // traits
} // Rcpp

#endif
