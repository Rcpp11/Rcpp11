#ifndef Rcpp_api_meat_sugar_h
#define Rcpp_api_meat_sugar_h

namespace Rcpp{
    
    namespace sugar {
        // default applyer for when Expression does not know how to 
        // apply itself to Target
        template <typename Target, typename Expression>
        struct sugar_vector_expression_op {
            inline void apply( Target& target, const Expression& expr ){
                std::copy( sugar_begin(expr), sugar_end(expr), target.begin() );
            }
        } ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    template <typename Target>
    void SugarVectorExpression<RTYPE,NA,Expr>::apply( Target& target ) const {
        if( std::is_base_of<sugar::custom_sugar_vector_expression, Expr>::value )
            get_ref().apply(target) ;
        else 
            sugar::sugar_vector_expression_op<Target,Expr>().apply( target, get_ref() ) ;  
    }
    
}

#endif
