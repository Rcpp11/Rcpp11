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
 * Identifies that the type if pair<const std::string,T> where T 
 * is a primitive type
 */
struct r_type_pairstring_primitive_tag{} ;

/**
 * Identifies that the associated type is pair<const std::(w)?string,std::(w)?string>
 */
struct r_type_pairstring_string_tag{} ;

/**
 * Indentifies pair<const std::string,T>
 */
struct r_type_pairstring_generic_tag{} ;

/**
 * Identifies a pair<const KEY, VALUE>, used to wrap map<KEY, VALUE>
 * VALUE can be anything that wraps, KEY can be anything we can build a String from
 */
struct r_type_pair_tag{} ;

/**
 * identifies a module object pointer
 */ 
struct r_type_module_object_pointer_tag{} ;

/**
 * identifies a module object const pointer 
 */ 
struct r_type_module_object_const_pointer_tag{} ;

/**
 * identifies a module object. Implementers of modules can define the 
 * r_type_traits to show that their object is handled
 */ 
struct r_type_module_object_tag{} ;

/**
 * identifies a reference to a module object. 
 */ 
struct r_type_module_object_reference_tag{} ;

/**
 * identifies a const reference to a module object. 
 */ 
struct r_type_module_object_const_reference_tag{} ;

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

/** 
 * special cases pair<string,T> to deal with map<string,T> etc ...
 */
template <typename T> struct r_type_traits< std::pair<const std::string,T> > { typedef r_type_pairstring_generic_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,int> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,const int> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,double> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,Rbyte> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,Rcomplex> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,bool> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,std::string> >{ typedef r_type_pairstring_string_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,std::wstring> >{ typedef r_type_pairstring_string_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,char> >{ typedef r_type_pairstring_string_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,wchar_t> >{ typedef r_type_pairstring_string_tag r_category ; } ;

template<> struct r_type_traits< std::pair<const std::string,unsigned int> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,float> >{ typedef r_type_pairstring_primitive_tag r_category ; } ;

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

/* long */
template<> struct r_type_traits<long>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,long> >{ typedef r_type_primitive_tag r_category ; } ;

/* unsigned long */
template<> struct r_type_traits<unsigned long>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,unsigned long> >{ typedef r_type_primitive_tag r_category ; } ;

/* long double */
template<> struct r_type_traits<long double>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,long double> >{ typedef r_type_primitive_tag r_category ; } ;

/* short */
template<> struct r_type_traits<short>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,short> >{ typedef r_type_primitive_tag r_category ; } ;

/* unsigned short */
template<> struct r_type_traits<unsigned short>{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,unsigned short> >{ typedef r_type_primitive_tag r_category ; } ;

/* std::complex<double> */
template<> struct r_type_traits< std::complex<double> >{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,std::complex<double> > >{ typedef r_type_primitive_tag r_category ; } ;

/* std::complex<float> */
template<> struct r_type_traits< std::complex<float> >{ typedef r_type_primitive_tag r_category ; } ;
template<> struct r_type_traits< std::pair<const std::string,std::complex<float> > >{ typedef r_type_primitive_tag r_category ; } ;

} // traits
} // Rcpp

#endif
