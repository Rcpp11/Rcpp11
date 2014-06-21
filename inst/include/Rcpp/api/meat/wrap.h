#ifndef Rcpp_api_meat_wrap_h
#define Rcpp_api_meat_wrap_h

namespace Rcpp{
    
    namespace internal{
        
        template <typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_primitive_tag){
            return materialize(import(first, last)) ;
        }

        template <typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_generic_tag ){
            return List(import(first, last));
        }
        
        template<typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_string_tag ){
            return CharacterVector(import(first,last)) ;
        }
              
        template<typename InputIterator, typename T>
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_pair_tag ){
            R_xlen_t n = std::distance( first, last ) ;
            const static int RTYPE = traits::r_sexptype_traits<typename T::second_type>::rtype ; 
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
       
    } // namespace internal

    
    template <typename T> 
    inline SEXP ContainerWrapper<T>::wrap(const T& object) {
        return internal::range_wrap( object.begin(), object.end() ) ;    
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
        return traits::wrap_type<T>::type::wrap(object) ; 
    }

} // namespace Rcpp

#endif
