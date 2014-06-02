#ifndef Rcpp__vector__SugarVectorExpression_h
#define Rcpp__vector__SugarVectorExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_vector_expression{} ;
    }
    
    template <int RTYPE, typename Expr>
    struct SugarVectorExpression : 
        public SugarVectorExpressionBase, 
        public CRTP<Expr>
    {
        using CRTP<Expr>::get_ref ;
        typedef typename traits::storage_type<RTYPE>::type value_type ;
        
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
