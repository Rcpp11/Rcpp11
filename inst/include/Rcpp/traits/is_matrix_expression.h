#ifndef Rcpp__traits__is_matrix_expression_h
#define Rcpp__traits__is_matrix_expression_h
  
namespace Rcpp {
    
    struct SugarMatrixExpressionBase {} ;
    
    namespace traits {
                           
        template <typename T>
        struct is_matrix_expression{
            typedef typename std::is_base_of<SugarMatrixExpressionBase, T>::type type ;
        } ; 
    }
}

#endif
