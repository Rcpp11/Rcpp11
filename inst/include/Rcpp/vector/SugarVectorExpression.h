#ifndef Rcpp__vector__SugarVectorExpression_h
#define Rcpp__vector__SugarVectorExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_vector_expression{} ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    struct SugarVectorExpression : 
        public VectorBase<RTYPE, NA, Expr>, 
        public SugarVectorExpressionBase
    {
        using VectorBase<RTYPE, NA, Expr>::get_ref ;
        
        template <typename Target>
        void apply( Target& target ) const ;
    
    } ;
    
}

#endif
