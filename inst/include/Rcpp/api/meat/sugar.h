#ifndef Rcpp_api_meat_sugar_h
#define Rcpp_api_meat_sugar_h

namespace Rcpp{
    
    namespace sugar {
        // default applyer for when Expression does not know how to 
        // apply itself to Target
        template <typename Target, int RTYPE, bool NA, typename Expr>
        struct sugar_vector_expression_op {
            inline void apply( Target& target, const SugarVectorExpression<RTYPE,NA,Expr>& expr ){
                std::copy( sugar_begin(expr), sugar_end(expr), target.begin() );
            }
        } ;
        
        // default applyer for when Expression does not know how to 
        // apply itself to Target
        template <typename Target, int RTYPE, bool NA, typename Expr>
        struct sugar_matrix_expression_op {
            inline void apply( Target& target, const SugarMatrixExpression<RTYPE,NA,Expr>& expr ){
                int nc = target.ncol(), nr = target.nrow() ;
                auto it = target.begin() ;
                for( R_len_t j=0; j<nc; j++) 
                    for( R_len_t i=0; i<nr; i++, ++it) 
                        *it = expr(i,j) ;
            }
        } ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    template <typename Target>
    void SugarVectorExpression<RTYPE,NA,Expr>::apply( Target& target ) const {
        if( std::is_base_of<sugar::custom_sugar_vector_expression, Expr>::value )
            get_ref().apply(target) ;
        else 
            sugar::sugar_vector_expression_op<Target,RTYPE,NA,Expr>().apply( target, *this ) ;  
    }
    
    template <int RTYPE, bool NA, typename Expr>
    template <typename Target>
    void SugarMatrixExpression<RTYPE,NA,Expr>::apply( Target& target ) const {
        if( std::is_base_of<sugar::custom_sugar_matrix_expression, Expr>::value )
            get_ref().apply(target) ;
        else 
            sugar::sugar_matrix_expression_op<Target,RTYPE,NA,Expr>().apply( target, *this ) ;  
    }
    
    
}

#endif
