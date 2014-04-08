#ifndef Rcpp_api_meat_sugar_h
#define Rcpp_api_meat_sugar_h

namespace Rcpp{
    
    template <int RTYPE, bool NA, typename VECTOR>
    template <typename Target>
    void SugarVectorExpression<RTYPE,NA,VECTOR>::apply( Target& target ) const {
        sugar::sugar_vector_expression_op<Target,VECTOR>().apply( target, get_ref() ) ;  
    }
    
}

#endif
