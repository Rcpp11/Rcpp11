#ifndef Rcpp__vector__SugarMatrixExpression_h
#define Rcpp__vector__SugarMatrixExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_matrix_expression{} ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    struct SugarMatrixExpression : 
        public MatrixBase<RTYPE, NA, Expr>, 
        public SugarMatrixExpressionBase
    {
        using MatrixBase<RTYPE, NA, Expr>::get_ref ;
        
        template <typename Target>
        void apply( Target& target ) const ;
    
    } ;
    
}

#endif
