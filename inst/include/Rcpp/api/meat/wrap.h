#ifndef Rcpp_api_meat_wrap_h
#define Rcpp_api_meat_wrap_h

namespace Rcpp{
    
    template <typename T> 
    inline SEXP wrap(const T& object){
        return traits::wrap_type<T>::type::wrap(object) ; 
    }

    template <typename T> struct ModuleObjectWrapper{
        static inline SEXP wrap(const T& object) { 
            Rcpp::XPtr<T> xp( new T(object), true ) ;
            Function maker = Environment::Rcpp11_namespace()[ "cpp_object_maker"] ;
            return maker( typeid(T).name() , xp ) ;
        }
    } ;
    
    
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
                RCPP_SET_VECTOR_ELT( x, i, Rcpp::wrap(first->second) );
                SET_STRING_ELT( names, i, buffer.get_sexp() ) ;
            }
            ::Rf_setAttrib( x, R_NamesSymbol, names) ;
            return x ;
        }
  

} // namespace internal

    
} // namespace Rcpp

#endif
