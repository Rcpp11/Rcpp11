#ifndef Rcpp__traits__is_vector_expression_h
#define Rcpp__traits__is_vector_expression_h
  
namespace Rcpp {
    
    struct SugarVectorExpressionBase {} ;
    
    namespace traits {
                           
        template <typename T>
        struct is_vector_expression {
            typedef typename std::is_base_of<SugarVectorExpressionBase, T>::type type;
        } ;
        
    }
}

#endif
