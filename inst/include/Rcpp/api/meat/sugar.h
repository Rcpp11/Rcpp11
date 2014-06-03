#ifndef Rcpp_api_meat_sugar_h
#define Rcpp_api_meat_sugar_h

namespace Rcpp{
    
    namespace sugar {
        
        // default applyer for when Expression does not know how to 
        // apply itself to Target
        template <typename Target, int RTYPE, typename eT, typename Expr>
        struct sugar_vector_expression_op {
            inline void apply( Target& target, const SugarVectorExpression<eT, Expr>& expr ){
                std::copy( sugar_begin(expr), sugar_end(expr), target.begin() );
            }
        } ;
        
        template <typename Target, typename eT, typename Expr>
        struct sugar_vector_expression_op<Target, VECSXP, eT, Expr> {
            inline void apply( Target& target, const SugarVectorExpression<eT,Expr>& expr ){
                if( std::is_convertible<eT,SEXP>::value ) {
                    std::copy( sugar_begin(expr), sugar_end(expr), target.begin() );
                } else {
                    std::transform( sugar_begin(expr), sugar_end(expr), target.begin(), [](storage x){
                            return wrap(x) ;
                    });    
                }
            }
        } ;
        
        
        // default applyer for when Expression does not know how to 
        // apply itself to Target
        template <typename Target, typename eT, typename Expr>
        struct sugar_matrix_expression_op {
            inline void apply( Target& target, const SugarMatrixExpression<eT,Expr>& expr ){
                int nc = target.ncol(), nr = target.nrow() ;
                auto it = target.begin() ;
                for( int j=0; j<nc; j++) 
                    for( int i=0; i<nr; i++, ++it) 
                        *it = expr(i,j) ;
            }
        } ;
    }
    
    template <typename eT, typename Expr>
    template <typename Target>
    void SugarVectorExpression<eT,Expr>::apply( Target& target ) const {
        if( std::is_base_of<sugar::custom_sugar_vector_expression, Expr>::value )
            get_ref().apply(target) ;
        else 
            sugar::sugar_vector_expression_op<Target, traits::r_sexptype_traits<eT>::rtype, eT, Expr>().apply( target, *this ) ;  
    }
    
    template <typename eT, typename Expr>
    template <typename Target>
    void SugarMatrixExpression<eT,Expr>::apply( Target& target ) const {
        if( std::is_base_of<sugar::custom_sugar_matrix_expression, Expr>::value )
            get_ref().apply(target) ;
        else 
            sugar::sugar_matrix_expression_op<Target,eT,Expr>().apply( target, *this ) ;  
    }
    
    
}

#endif
