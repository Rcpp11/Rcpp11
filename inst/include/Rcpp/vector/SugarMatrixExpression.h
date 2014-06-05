#ifndef Rcpp__vector__SugarMatrixExpression_h
#define Rcpp__vector__SugarMatrixExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_matrix_expression{} ;
    }
    
    template <typename eT, typename Expr>
    struct SugarMatrixExpression : 
        public SugarMatrixExpressionBase, 
        public CRTP<Expr>
    {
        using CRTP<Expr>::get_ref;
        typedef Expr expr_type ;
        typedef eT value_type ;
        typedef typename std::integral_constant<int, traits::r_sexptype_traits<eT>::rtype >::type r_type ;
        
        template <typename Target>
        void apply( Target& target ) const ;
    
        inline int nrow() const { return get_ref().nrow(); }
        inline int ncol() const { return get_ref().ncol(); }
        inline int size() const { return get_ref().size(); }
        
        inline eT operator()(int i, int j) const { return get_ref()(i,j) ; }
    } ;
    
}

#endif
