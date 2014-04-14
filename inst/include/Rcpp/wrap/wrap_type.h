#ifndef Rcpp_wrap_wrap_type_h
#define Rcpp_wrap_wrap_type_h
 
namespace Rcpp{
namespace traits{
    
    template <typename T>
    struct wrap_type {
        typedef typename Rcpp::traits::wrap_type_traits<T>::wrap_category wrap_category ;
        const static bool has_matrix_interface = Rcpp::traits::is_matrix_expression<T>::type::value ;
        const static bool has_iterator = Rcpp::traits::has_iterator<T>::value ;
        const static bool is_primitive = std::is_same< wrap_category , Rcpp::traits::wrap_type_primitive_tag>::value ;
        const static bool is_enum      = std::is_enum<T>::value  ;
        const static bool is_sexp_convertible = std::is_convertible<T,SEXP>::value ;
        const static bool is_sugar = Rcpp::traits::is_vector_expression<T>::type::value ;
         
        typedef typename std::conditional< 
            is_sexp_convertible, 
            typename Rcpp::SexpConvertibleWrapper<T>,
            typename std::conditional<
                    is_primitive, 
                    typename Rcpp::PrimitiveWrapper<T>,
                    typename std::conditional<
                        is_enum,
                        Rcpp::EnumWrapper<T>,
                        typename std::conditional<
                            is_sugar,
                            typename Rcpp::SugarExpressionWrapper<T>,
                            typename std::conditional<
                                has_matrix_interface,
                                typename Rcpp::MatrixWrapper<T>,
                                typename std::conditional<
                                    has_iterator, 
                                    typename Rcpp::ContainerWrapper<T>, 
                                    typename Rcpp::Wrapper<T>
                                    >::type
                                >::type
                            >::type
                        >::type
                    >::type
            >::type type ;
    } ;
    
}
}

#endif
