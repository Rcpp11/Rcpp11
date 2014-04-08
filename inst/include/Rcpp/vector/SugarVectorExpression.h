#ifndef Rcpp__vector__SugarVectorExpression_h
#define Rcpp__vector__SugarVectorExpression_h

namespace Rcpp{
    
    namespace sugar {
        
        template <typename Target, typename Expression>
        struct sugar_vector_expression_op {
            inline void apply( Target& target, const Expression& expr ){
                int n = expr.size() ;
                auto it = target.begin() ;
                for(int i=0; i<n; i++, ++it){
                    *it = expr[i] ;    
                }        
            }
        } ;
        
    }
    
    template <int RTYPE, bool NA, typename VECTOR>
    struct SugarVectorExpression : 
        public VectorBase<RTYPE, NA, VECTOR>, 
        public SugarVectorExpressionBase
    {
        using VectorBase<RTYPE, NA, VECTOR>::get_ref ;
        
        template <typename Target>
        void apply( Target& target ) const ;
    
    } ;
    
}

#endif
