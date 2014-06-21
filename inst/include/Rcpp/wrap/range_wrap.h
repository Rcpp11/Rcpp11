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
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_primitive_tag) ;

        template<typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_enum_tag ){
            #if defined(RCPP_HAS_UNDERLYING_TYPE)
                return range_wrap_dispatch<InputIterator, typename std::underlying_type<T>::type >( first, last ) ;
            #else
                return range_wrap_dispatch<InputIterator, int>( first, last ) ;
            #endif
        }
        
        template <typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_generic_tag ) ;
        
        /**
         * Range based wrap implementation for iterators over std::string
         *
         * This produces an unnamed character vector
         */
        template<typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_string_tag ) ;
        
        /**
         * Range wrap dispatch for iterators over std::pair<const KEY, VALUE>
         */
        template<typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_pair_tag ) ;
        
        /**
         * Dispatcher for all range based wrap implementations
         *
         * This uses the Rcpp::traits::r_type_traits to perform further dispatch
         */
        template<typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch( InputIterator first, InputIterator last ){
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
