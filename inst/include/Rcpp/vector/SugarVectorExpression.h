#ifndef Rcpp__vector__SugarVectorExpression_h
#define Rcpp__vector__SugarVectorExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_vector_expression{} ;
    }
    
    template <typename eT, typename Expr>
    struct SugarVectorExpression : 
        public SugarVectorExpressionBase, 
        public CRTP<Expr>
    {
        using CRTP<Expr>::get_ref ;
        typedef Expr expr_type ;
        typedef eT value_type ;
        typedef typename std::integral_constant<int, traits::r_sexptype_traits<eT>::rtype >::type r_type ;
        
        inline R_xlen_t size() const { 
            return get_ref().size() ;
        }
    
        template <typename Target>
        void apply( Target& target ) const ;
        
        template <typename Target>
        void apply_parallel( Target& target ) const ;
    
    } ;
    
    template <typename eT, typename Expr>
    inline SEXP materialize( const SugarVectorExpression<eT, Expr>& ) ;
    
}

#endif
