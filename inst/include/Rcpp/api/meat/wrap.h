#ifndef Rcpp_api_meat_wrap_h
#define Rcpp_api_meat_wrap_h

namespace Rcpp{
    
    namespace internal{
        
        template <typename InputIterator, typename KEY, typename VALUE, int RTYPE>
        inline SEXP range_wrap_dispatch___impl__pair( InputIterator first, InputIterator last, std::true_type ){
            size_t size = std::distance( first, last ) ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            
            Shield<SEXP> names = Rf_allocVector(STRSXP, size) ;
            Shield<SEXP> x = Rf_allocVector(RTYPE, size) ;
            STORAGE* ptr = Rcpp::internal::r_vector_start<RTYPE>( x ) ;
            Rcpp::String buffer ;
            for( size_t i = 0; i < size ; i++, ++first){
                buffer = first->first ;
                ptr[i] = first->second ;
                SET_STRING_ELT( names, i, buffer.get_sexp() ) ;
            }
            ::Rf_setAttrib( x, R_NamesSymbol, names) ;
            return x ;
        }
                        
        template <typename InputIterator, typename KEY, typename VALUE, int RTYPE>
        inline SEXP range_wrap_dispatch___impl__pair( InputIterator first, InputIterator last, std::false_type ){
            size_t size = std::distance( first, last ) ;
            
            Shield<SEXP> names = Rf_allocVector(STRSXP, size) ;
            Shield<SEXP> x = Rf_allocVector(VECSXP, size) ;
            Rcpp::String buffer ;
            for( size_t i = 0; i < size ; i++, ++first){
                buffer = first->first ;    
                SET_VECTOR_ELT( x, i, Rcpp::wrap(first->second) );
                SET_STRING_ELT( names, i, buffer.get_sexp() ) ;
            }
            ::Rf_setAttrib( x, R_NamesSymbol, names) ;
            return x ;
        }
  
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
        inline SEXP range_wrap_dispatch___impl( InputIterator first, InputIterator last, ::Rcpp::traits::r_type_pairstring_string_tag ){
            size_t size = std::distance( first, last ) ;
            Shield<SEXP> x = Rf_allocVector( STRSXP, size ) ;
            Shield<SEXP> names = Rf_allocVector( STRSXP, size ) ;
            for( size_t i = 0; i < size ; i++, ++first){
                SET_STRING_ELT( x, i, String( first->second ).get_sexp() ) ;
                SET_STRING_ELT( names, i, String( first->first).get_sexp() ) ;
            }
            ::Rf_setAttrib( x, R_NamesSymbol, names ) ;
            return x ;
        
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
