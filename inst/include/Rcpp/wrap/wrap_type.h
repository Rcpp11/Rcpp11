#ifndef Rcpp_wrap_wrap_type_h
#define Rcpp_wrap_wrap_type_h
 
namespace Rcpp{
    namespace traits{
         
        template <typename T>
        struct is_wrappable : public std::integral_constant<bool, 
            !std::is_base_of< DisabledWrapper, Wrapper<T> >::value ||
            Rcpp::traits::is_matrix_expression<T>::type::value ||
            Rcpp::traits::has_iterator<T>::value ||
            std::is_same< typename Rcpp::traits::wrap_type_traits<T>::wrap_category , Rcpp::traits::wrap_type_primitive_tag>::value ||
            std::is_enum<T>::value ||
            std::is_convertible<T,SEXP>::value ||
            is_vector_expression<T>::value ||
            is_lazy_vector<T>::type::value 
        >{} ;
        
        template <typename T>
        struct wrap_type {
            const static bool has_explicit_wrapper = !std::is_base_of< DisabledWrapper, Wrapper<T> >::value ;
            const static bool has_matrix_interface = Rcpp::traits::is_matrix_expression<T>::type::value ;
            const static bool has_iterator = Rcpp::traits::has_iterator<T>::value ;
            const static bool is_enum      = std::is_enum<T>::value  ;
            const static bool is_sexp_convertible = std::is_convertible<T,SEXP>::value ;
            const static bool is_sugar = is_vector_expression<T>::value ;
            const static bool is_lazy = is_lazy_vector<T>::type::value ; 
            const static bool is_prim = std::is_same< 
                typename Rcpp::traits::wrap_type_traits<T>::wrap_category , 
                Rcpp::traits::wrap_type_primitive_tag
            >::value ;
                    
            typedef typename std::conditional<
                has_explicit_wrapper, 
                Wrapper<T>, 
                typename std::conditional<
                    is_sexp_convertible, 
                    typename Rcpp::SexpConvertibleWrapper<T>,
                    typename std::conditional<
                        is_prim, 
                        typename Rcpp::PrimitiveWrapper<T>,
                        typename std::conditional<
                            is_enum,
                            Rcpp::EnumWrapper<T>,
                            typename std::conditional<
                                is_sugar,
                                typename Rcpp::SugarExpressionWrapper<T>,
                                typename std::conditional<
                                    is_lazy,
                                    typename Rcpp::LazyVectorWrapper<T>,
                                    typename std::conditional<
                                        has_matrix_interface,
                                        typename Rcpp::MatrixWrapper<T>,
                                        typename std::conditional<
                                            has_iterator,
                                            typename Rcpp::ContainerWrapper<T>,
                                            DisabledWrapper
                                        >::type    
                                    >::type
                                >::type
                            >::type
                        >::type
                    >::type
                >::type
            >::type type;
        } ;
        
    }
}

#endif
