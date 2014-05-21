#ifndef Rcpp__traits__get_compatible_r_vector_type__h
#define Rcpp__traits__get_compatible_r_vector_type__h

namespace Rcpp{
    namespace traits{

        // not a primitive
        template <typename T, bool prim>
        struct get_compatible_r_vector_type__dispatch {
            enum { 
                rtype = r_sexptype_traits<typename std::decay<T>::type::stored_type>::rtype 
            } ; 
        } ;
        
        // a primitive
        template <typename T>
        struct get_compatible_r_vector_type__dispatch<T,true> {
            enum { 
                rtype = r_sexptype_traits<T>::rtype 
            } ; 
        } ;
        
        template <typename T>
        struct get_compatible_r_vector_type {
            enum{
               rtype = get_compatible_r_vector_type__dispatch<T, is_primitive<typename std::decay<T>::type >::value >::rtype  
            } ;
        } ;
        
        template <int N>
        struct get_compatible_r_vector_type< char[N] >{
            enum{
              rtype = STRSXP    
            } ;
        } ;
        
        template <>
        struct get_compatible_r_vector_type< const char* >{
            enum{
              rtype = STRSXP    
            } ;
        } ;
        
        template <>
        struct get_compatible_r_vector_type< Rcpp::Na_Proxy >{
            enum{
              rtype = -1    
            } ;
        } ;
        
        template <>
        struct get_compatible_r_vector_type< traits::named_object<Rcpp::Na_Proxy> >{
            enum{
              rtype = -1    
            } ;
        } ;
        
    }
}

#endif
