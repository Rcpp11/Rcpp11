#ifndef Rcpp__vector__SugarVectorExpression_h
#define Rcpp__vector__SugarVectorExpression_h

namespace Rcpp{
    
    namespace sugar{
        struct custom_sugar_vector_expression{} ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    struct SugarVectorExpression : 
        public SugarVectorExpressionBase, 
        public CRTP<Expr>
    {
        using CRTP<Expr>::get_ref ;
    
        struct r_type : std::integral_constant<int,RTYPE>{} ;
        typedef typename traits::storage_type<RTYPE>::type stored_type ; 
        typedef typename traits::storage_type<RTYPE>::type elem_type   ;
        
        inline stored_type operator[]( int i) const {
            return get_ref()[i] ;
        }
        
        inline int size() const { 
            return get_ref().size() ;
        }
    
        template <typename Target>
        void apply( Target& target ) const ;
    
    } ;
    
}

#endif
