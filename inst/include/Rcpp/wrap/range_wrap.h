// Copyright (C) 2010 - 2013  Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013  Rice University
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Rcpp_wrap_range_wrap_h
#define Rcpp_wrap_range_wrap_h
 
namespace Rcpp{
namespace internal{
	
// {{{ range wrap 
// {{{ unnamed range wrap

template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch( InputIterator first, InputIterator last ) ;

/**
 * Range based wrap implementation that deals with iterator over
 * primitive types (int, double, etc ...)
 * 
 * This produces an unnamed vector of the appropriate type
 */
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_primitive_tag){ 
	return primitive_range_wrap__impl<InputIterator,T>( first, last, typename ::Rcpp::traits::r_sexptype_needscast<T>() ) ;
}

template<typename InputIterator, typename T>
inline SEXP range_wrap_enum__dispatch( InputIterator first, InputIterator last, std::true_type ){
	size_t size = std::distance( first, last ) ;
	Scoped<SEXP> x = Rf_allocVector( LGLSXP, size );
	                                          
	int __trip_count = size >> 2 ;
	int* start = r_vector_start<LGLSXP>(x) ;
	int i = 0 ;
	for ( ; __trip_count > 0 ; --__trip_count) { 
    	start[i] = first[i] ; i++ ;            
    	start[i] = first[i] ; i++ ;            
    	start[i] = first[i] ; i++ ;            
    	start[i] = first[i] ; i++ ;            
	}                                            
	switch (size - i){                          
	  case 3:                                    
	      start[i] = first[i] ; i++ ;             
      case 2:                                    
	      start[i] = first[i] ; i++ ;             
	  case 1:                                    
	      start[i] = first[i] ; i++ ;             
	  case 0:                                    
	  default:                                   
	      {}                         
	}                                            
	
	return wrap_extra_steps<T>( x ) ;
    
}
template<typename InputIterator, typename T>
inline SEXP range_wrap_enum__dispatch( InputIterator first, InputIterator last, std::false_type ){
    return range_wrap_dispatch<InputIterator, typename std::underlying_type<T>::type >( first, last ) ;
}

template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_enum_tag ){
    return range_wrap_enum__dispatch<InputIterator,T>( first, last, 
        typename std::is_same< 
            typename std::integral_constant<int, ::Rcpp::traits::r_sexptype_traits<T>::rtype >::type, 
            typename std::integral_constant<int,LGLSXP>::type
        >::type() 
    ); 
}

/** 
 * range based wrap implementation that deals with iterators over 
 * some type U. each U object is itself wrapped
 * 
 * This produces an unnamed generic vector (list)
 */
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___generic( InputIterator first, InputIterator last ){ 
	size_t size = std::distance( first, last ) ;
	Scoped<SEXP> x = Rf_allocVector( VECSXP, size );
	size_t i =0 ;
	while( i < size ){
		RCPP_SET_VECTOR_ELT( x, i, ::Rcpp::wrap(*first) ) ;
		i++ ;
		++first ;
	}
	return x ;
}

template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_generic_tag ){ 
	return range_wrap_dispatch___generic<InputIterator, T>( first, last ) ;
}

// modules
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_module_object_pointer_tag ){ 
	return range_wrap_dispatch___generic<InputIterator, T>( first, last ) ;
}
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_module_object_const_pointer_tag ){ 
	return range_wrap_dispatch___generic<InputIterator, T>( first, last ) ;
}
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_module_object_tag ){ 
	return range_wrap_dispatch___generic<InputIterator, T>( first, last ) ;
}
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_module_object_reference_tag ){ 
	return range_wrap_dispatch___generic<InputIterator, T>( first, last ) ;
}
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_module_object_const_reference_tag ){ 
	return range_wrap_dispatch___generic<InputIterator, T>( first, last ) ;
}



/**
 * Range based wrap implementation for iterators over std::string
 * 
 * This produces an unnamed character vector
 */
template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_string_tag ){
	size_t size = std::distance( first, last ) ;
	Scoped<SEXP> x = Rf_allocVector( STRSXP, size ) ;
	size_t i = 0 ;
	while( i < size ){
		SET_STRING_ELT( x, i, make_charsexp(*first) ) ;
		i++ ;
		++first ;
	}
	return x ;
}

// }}}

// {{{ named range wrap

/** 
 * range based wrap implementation that deals with iterators over
 * pair<const string,T> where T is a primitive type : int, double ...
 * 
 * This version is used when there is no need to cast T
 * 
 * This produces a named R vector of the appropriate type
 */
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl__cast( InputIterator first, InputIterator last, std::false_type ){
	size_t size = std::distance( first, last ) ;
	const int RTYPE = ::Rcpp::traits::r_sexptype_traits<typename T::second_type>::rtype ;
	Scoped<SEXP> x = Rf_allocVector( RTYPE, size );
	Scoped<SEXP> names = Rf_allocVector( STRSXP, size ) ;
	typedef typename ::Rcpp::traits::storage_type<RTYPE>::type CTYPE ;
	CTYPE* start = r_vector_start<RTYPE>(x) ;
	size_t i =0;
	std::string buf ; 
	for( ; i<size; i++, ++first){
		start[i] = (*first).second ;
		buf = (*first).first ;
		SET_STRING_ELT( names, i, Rf_mkChar(buf.c_str()) ) ;
	}
	::Rf_setAttrib( x, R_NamesSymbol, names ) ;
	return wrap_extra_steps<T>( x ) ;
}

/** 
 * range based wrap implementation that deals with iterators over
 * pair<const string,T> where T is a primitive type : int, double ...
 * 
 * This version is used when T needs to be cast to the associated R
 * type
 * 
 * This produces a named R vector of the appropriate type
 */
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl__cast( InputIterator first, InputIterator last, std::true_type ){
	size_t size = std::distance( first, last ) ;
	const int RTYPE = ::Rcpp::traits::r_sexptype_traits<typename T::second_type>::rtype ;
	Scoped<SEXP> x = Rf_allocVector( RTYPE, size ) ;
	Scoped<SEXP> names = Rf_allocVector( STRSXP, size ) ;
	typedef typename ::Rcpp::traits::storage_type<RTYPE>::type CTYPE ;
	CTYPE* start = r_vector_start<RTYPE>(x) ;
	size_t i =0;
	std::string buf ; 
	for( ; i<size; i++, ++first){
		start[i] = static_cast<CTYPE>( first->second );
		buf = first->first ;
		SET_STRING_ELT( names, i, Rf_mkChar(buf.c_str()) ) ;
	}
	::Rf_setAttrib( x, R_NamesSymbol, names ) ;
	return wrap_extra_steps<T>( x ) ;
}


/** 
 * range based wrap implementation that deals with iterators over
 * pair<const string,T> where T is a primitive type : int, double ...
 * 
 * This dispatches further depending on whether the type needs 
 * a cast to fit into the associated R type
 * 
 * This produces a named R vector of the appropriate type
 */
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_pairstring_primitive_tag){ 
	return range_wrap_dispatch___impl__cast<InputIterator,T>( first, last, 
		typename ::Rcpp::traits::r_sexptype_needscast<typename T::second_type>() ) ;
}

/**
 * Range based wrap implementation that deals with iterators over
 * pair<const string, U> where U is wrappable. This is the kind of 
 * iterators that are produced by map<string,U>
 * 
 * This produces a named generic vector (named list). The first 
 * element of the list contains the result of a call to wrap on the 
 * object of type U, etc ...
 *
 * The names are taken from the keys
 */
template <typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_pairstring_generic_tag ){ 
	size_t size = std::distance( first, last ) ;
	Scoped<SEXP> x = Rf_allocVector( VECSXP, size );
	Scoped<SEXP> names = Rf_allocVector( STRSXP, size ) ;
	size_t i =0 ;
	std::string buf ;
	SEXP element = R_NilValue ;
	while( i < size ){
		element = ::Rcpp::wrap( first->second ) ;
		buf = first->first ;
		RCPP_SET_VECTOR_ELT( x, i, element ) ;
		RCPP_SET_VECTOR_ELT( names, i, Rf_mkChar(buf.c_str()) ) ; 
		i++ ;
		++first ;
	}
	::Rf_setAttrib( x, R_NamesSymbol, names ) ;
	return x ;
}


/**
 * Range based wrap for iterators over std::pair<const std::(w)?string, std::(w)?string>
 *
 * This is mainly used for wrapping map<string,string> and friends 
 * which happens to produce iterators over pair<const string, string>
 *
 * This produces a character vector containing copies of the 
 * string iterated over. The names of the vector is set to the keys
 * of the pair
 */
template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_pairstring_string_tag ){
	size_t size = std::distance( first, last ) ;
	Scoped<SEXP> x = Rf_allocVector( STRSXP, size ) ;
	Scoped<SEXP> names = Rf_allocVector( STRSXP, size ) ;
	for( size_t i = 0; i < size ; i++, ++first){
		SET_STRING_ELT( x, i, make_charsexp( first->second ) ) ;
		SET_STRING_ELT( names, i, make_charsexp( first->first) ) ;
	}
	::Rf_setAttrib( x, R_NamesSymbol, names ) ;
	return x ;

}

/** 
 * iterating over pair<const int, VALUE>
 * where VALUE is some primitive type
 */
template <typename InputIterator, typename KEY, typename VALUE, int RTYPE>
inline SEXP range_wrap_dispatch___impl__pair( InputIterator first, InputIterator last, std::true_type ) ;

/** 
 * iterating over pair<const int, VALUE>
 * where VALUE is a type that needs wrapping
 */
template <typename InputIterator, typename KEY, typename VALUE, int RTYPE>
inline SEXP range_wrap_dispatch___impl__pair( InputIterator first, InputIterator last, std::false_type ) ;


/**
 * Range wrap dispatch for iterators over std::pair<const int, T>
 */
template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_pair_tag ){
	typedef typename T::second_type VALUE ;
	typedef typename T::first_type KEY ;
	
	return range_wrap_dispatch___impl__pair<
			InputIterator,
			KEY, 
			VALUE, 
			Rcpp::traits::r_sexptype_traits<VALUE>::rtype
		>( first, last, 
		typename Rcpp::traits::is_primitive<VALUE>::type()
		) ;
}

// }}}

/**
 * Dispatcher for all range based wrap implementations
 * 
 * This uses the Rcpp::traits::r_type_traits to perform further dispatch
 */
template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch( InputIterator first, InputIterator last ){
	RCPP_DEBUG( "range_wrap_dispatch< InputIterator = \n%s , T = %s>\n", DEMANGLE(InputIterator), DEMANGLE(T) ) ;
	return range_wrap_dispatch___impl<InputIterator,T>( first, last, typename ::Rcpp::traits::r_type_traits<T>::r_category() ) ;
}

// we use the iterator trait to make the dispatch
/**
 * range based wrap. This uses the std::iterator_traits class
 * to perform further dispatch
 */
template <typename InputIterator>
inline SEXP range_wrap(InputIterator first, InputIterator last){
	return range_wrap_dispatch<InputIterator,typename std::remove_reference<typename std::iterator_traits<InputIterator>::value_type>::type >( first, last ) ;
}
// }}}
        
}
}

#endif
