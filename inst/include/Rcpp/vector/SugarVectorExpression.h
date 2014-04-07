#ifndef Rcpp__vector__VectorExpression_h
#define Rcpp__vector__VectorExpression_h

namespace Rcpp{
         
    struct SugarVectorExpressionBase {} ;
    
    template <int RTYPE, bool NA, typename VECTOR>
    struct SugarVectorExpression : 
        public VectorBase<RTYPE, NA, VECTOR>, 
        public SugarVectorExpressionBase
        {} ;
    
}

#endif
