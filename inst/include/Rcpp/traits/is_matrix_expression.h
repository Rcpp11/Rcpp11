#ifndef Rcpp__traits__is_matrix_expression_h
#define Rcpp__traits__is_matrix_expression_h
  
namespace Rcpp {
namespace traits {
                       
    struct MatrixExpression{} ;
    
    template <typename T>
    using is_matrix_expression = typename std::is_base_of<MatrixExpression, T>::type ;
    
}
}

#endif
