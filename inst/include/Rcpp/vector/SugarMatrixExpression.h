#ifndef Rcpp__vector__SugarMatrixExpression_h
#define Rcpp__vector__SugarMatrixExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_matrix_expression{} ;
    }
    
    template <typename eT, typename Expr>
    struct SugarMatrixExpression : 
        public MatrixBase<eT, Expr>, 
        public SugarMatrixExpressionBase
    {
        using MatrixBase<eT, Expr>::get_ref ;
        
        template <typename Target>
        void apply( Target& target ) const ;
    
    } ;
    
}

#endif
