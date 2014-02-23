#ifndef Rcpp_wrap_range_wrap_h
#define Rcpp_wrap_range_wrap_h
 
namespace Rcpp{
namespace internal{
	
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
	Shield<SEXP> x = Rf_allocVector( LGLSXP, (int)size );
	std::copy( first, last, LOGICAL(x)) ;   
	return x ;
}
template<typename InputIterator, typename T>
inline SEXP range_wrap_enum__dispatch( InputIterator first, InputIterator last, std::false_type ){
    return range_wrap_dispatch<InputIterator, typename std::underlying_type<T>::type >( first, last ) ;
}

template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_enum_tag ){
    return range_wrap_enum__dispatch<InputIterator,T>( first, last, 
        typename std::integral_constant<bool, ::Rcpp::traits::r_sexptype_traits<T>::rtype == LGLSXP>::type()
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
	Shield<SEXP> x = Rf_allocVector( VECSXP, (int)size );
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


/**
 * Range based wrap implementation for iterators over std::string
 * 
 * This produces an unnamed character vector
 */
template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_string_tag ){
	size_t size = std::distance( first, last ) ;
	Shield<SEXP> x = Rf_allocVector( STRSXP, (int)size ) ;
	size_t i = 0 ;
	while( i < size ){
		SET_STRING_ELT( x, i, make_charsexp(*first) ) ;
		i++ ;
		++first ;
	}
	return x ;
}

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
	Shield<SEXP> x = Rf_allocVector( RTYPE, (int)size );
	Shield<SEXP> names = Rf_allocVector( STRSXP, size ) ;
	typedef typename ::Rcpp::traits::storage_type<RTYPE>::type CTYPE ;
	CTYPE* start = r_vector_start<RTYPE>(x) ;
	int i =0;
	std::string buf ; 
	for( ; i<size; i++, ++first){
		start[i] = (*first).second ;
		buf = (*first).first ;
		SET_STRING_ELT( names, i, Rf_mkChar(buf.c_str()) ) ;
	}
	::Rf_setAttrib( x, R_NamesSymbol, names ) ;
	return x ;
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
	Shield<SEXP> x = Rf_allocVector( RTYPE, size ) ;
	Shield<SEXP> names = Rf_allocVector( STRSXP, size ) ;
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
	return x ;
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
	Shield<SEXP> x = Rf_allocVector( VECSXP, size );
	Shield<SEXP> names = Rf_allocVector( STRSXP, size ) ;
	size_t i =0 ;
	std::string buf ;
	SEXP element = R_NilValue ;
	while( i < size ){
		element = ::Rcpp::wrap( first->second ) ;
		buf = first->first ;
		RCPP_SET_VECTOR_ELT( x, i, element ) ;
		SET_STRING_ELT( names, i, Rf_mkChar(buf.c_str()) ) ; 
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
	Shield<SEXP> x = Rf_allocVector( STRSXP, size ) ;
	Shield<SEXP> names = Rf_allocVector( STRSXP, size ) ;
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

/**
 * Dispatcher for all range based wrap implementations
 * 
 * This uses the Rcpp::traits::r_type_traits to perform further dispatch
 */
template<typename InputIterator, typename T>
inline SEXP range_wrap_dispatch( InputIterator first, InputIterator last ){
	typedef typename ::Rcpp::traits::r_type_traits<T>::r_category categ ;
    RCPP_DEBUG( "range_wrap_dispatch< InputIterator = \n%s , T = %s>, categ=%s\n", DEMANGLE(InputIterator), DEMANGLE(T), DEMANGLE(categ) ) ;
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
        
}
}

#endif
