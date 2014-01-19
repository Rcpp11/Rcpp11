#ifndef Rcpp__traits__is_module_object__h
#define Rcpp__traits__is_module_object__h

namespace Rcpp{
namespace traits{
      
	template <typename T> struct is_module_object : 
		public std::integral_constant<bool,
			std::is_same< typename r_type_traits<T>::r_category, r_type_module_object_tag >::value                ||
			std::is_same< typename r_type_traits<T>::r_category, r_type_module_object_pointer_tag >::value        ||
			std::is_same< typename r_type_traits<T>::r_category, r_type_module_object_const_pointer_tag >::value  ||
			std::is_same< typename r_type_traits<T>::r_category, r_type_module_object_reference_tag >::value      ||
			std::is_same< typename r_type_traits<T>::r_category, r_type_module_object_const_reference_tag >::value
		>{} ;

} // traits
} // Rcpp

#endif
