#ifndef Rcpp_api_meat_sugar_h
#define Rcpp_api_meat_sugar_h

namespace Rcpp{
    
    namespace sugar {
        
        template <typename Target, typename eT, typename Expr, bool>
        struct sugar_vector_expression_op ;
        
        // default applyer for when Expression does not know how to 
        // apply itself to Target
        template <typename Target, typename eT, typename Expr>
        struct sugar_vector_expression_op<Target,eT,Expr,true> {
            inline void apply( Target& target, const SugarVectorExpression<eT, Expr>& expr ){
                apply_parallel(target, expr ) ;
            }
            
            inline void apply_parallel( Target& target, const SugarVectorExpression<eT, Expr>& expr ){
                parallel::copy( sugar_begin(expr), sugar_end(expr), target.begin() );
            }
            
            inline void apply_serial( Target& target, const SugarVectorExpression<eT, Expr>& expr ){
                std::copy( sugar_begin(expr), sugar_end(expr), target.begin() );
            }
        } ;
        
        template <typename Target, typename eT, typename Expr>
        struct sugar_vector_expression_op<Target,eT,Expr,false> {
            
            inline void apply( Target& target, const SugarVectorExpression<eT,Expr>& expr ){
                return apply_parallel( target, expr ) ;
            }
            
            inline void apply_serial( Target& target, const SugarVectorExpression<eT,Expr>& expr ){
                typedef typename traits::r_vector_element_converter< Target::r_type::value >::type converter ;
                std::transform( sugar_begin(expr), sugar_end(expr), target.begin(), [](eT x){
                        return converter::get(x) ;
                });    
            }
            
            inline void apply_parallel( Target& target, const SugarVectorExpression<eT,Expr>& expr ){
                typedef typename traits::r_vector_element_converter< Target::r_type::value >::type converter ;
                parallel::transform( sugar_begin(expr), sugar_end(expr), target.begin(), [](eT x){
                        return converter::get(x) ;
                });    
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
            sugar::sugar_vector_expression_op<Target, eT, Expr, std::is_same<eT, typename Target::value_type >::value >().apply( target, *this ) ;  
    }
    
    template <typename eT, typename Expr>
    template <typename Target>
    void SugarVectorExpression<eT,Expr>::apply_serial( Target& target ) const {
        if( std::is_base_of<sugar::custom_sugar_vector_expression, Expr>::value )
            get_ref().apply_serial(target) ;
        else 
            sugar::sugar_vector_expression_op<Target, eT, Expr, std::is_same<eT, typename Target::value_type >::value >().apply_serial( target, *this ) ;  
    }
    
    template <typename eT, typename Expr>
    template <typename Target>
    void SugarVectorExpression<eT,Expr>::apply_parallel( Target& target ) const {
        if( std::is_base_of<sugar::custom_sugar_vector_expression, Expr>::value )
            get_ref().apply_parallel(target) ;
        else 
            sugar::sugar_vector_expression_op<Target, eT, Expr, std::is_same<eT, typename Target::value_type >::value >().apply_parallel( target, *this ) ;  
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
