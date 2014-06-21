#ifndef Rcpp_api_meat_wrap_h
#define Rcpp_api_meat_wrap_h

namespace Rcpp{
    
    template <typename Iterator, typename value_type> 
    struct RangeWrapper {
        static inline SEXP wrap(Iterator first, Iterator last) {
            return materialize(import(first, last)) ;    
        }
    } ;
    
    template <typename Iterator, typename KEY, typename VALUE>
    struct RangeWrapper<Iterator, std::pair<const KEY, VALUE> >{
        static inline SEXP wrap(Iterator first, Iterator last) {
            R_xlen_t n = std::distance( first, last ) ;
            const static int RTYPE = traits::r_sexptype_traits<VALUE>::rtype ; 
            typedef Vector<RTYPE> Vec ;
            typedef typename traits::r_vector_element_converter<RTYPE>::type converter ;
            
            Vec vec(n);
            CharacterVector names(n) ;
            auto vec_it = vec.begin() ;
            auto names_it = names.begin() ;
            for( R_xlen_t i = 0; i<n; i++, ++vec_it, ++names_it, ++first){
                *names_it = first->first ;
                *vec_it   = converter::get(first->second) ;
            }
            vec.names() = names ;
            return vec ;       
        }    
    } ;
    
    template <typename InputIterator>
    inline SEXP wrap_range(InputIterator first, InputIterator last){
        typedef RangeWrapper<InputIterator, typename std::iterator_traits<InputIterator>::value_type > Wrapper ;
        return Wrapper::wrap(first, last ) ;
    }

    
    template <typename T> 
    inline SEXP ContainerWrapper<T>::wrap(const T& object) {
        return wrap_range( object.begin(), object.end() ) ;    
    }
    
    template <typename T> 
    inline SEXP MatrixWrapper<T>::wrap(const T& object) {
        return Matrix< traits::r_sexptype_traits<typename T::value_type>::rtype  >( object ) ;    
    }
    
    template <typename T> 
    inline SEXP PrimitiveWrapper<T>::wrap(const T& object) { 
        return Vector< traits::r_sexptype_traits<T>::rtype >{ 
            traits::r_vector_element_converter< traits::r_sexptype_traits<T>::rtype>::type::get(object)       
        } ;
    }
    
    template <typename T> 
    inline SEXP wrap(const T& object){
        static_assert( traits::is_wrappable<T>::value, "unwrappable type" ) ;
        return traits::wrap_type<T>::type::wrap(object) ; 
    }

} // namespace Rcpp

#endif
