#ifndef Rcpp__vector__SugarVectorExpression_h
#define Rcpp__vector__SugarVectorExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_vector_expression{} ;
    }
    
    template <typename Expr>
    struct SugarVectorExpression : 
        public SugarVectorExpressionBase, 
        public CRTP<Expr>
    {
        using CRTP<Expr>::get_ref ;
    
        typedef Expr expr_type ;
        typedef typename Expr::value_type value_type ;
        
        inline value_type operator[]( R_xlen_t i) const {
            return get_ref()[i] ;
        }
        
        inline R_xlen_t size() const { 
            return get_ref().size() ;
        }
    
        template <typename Target>
        void apply( Target& target ) const ;
    
    } ;
    
}

#endif
