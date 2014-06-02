#ifndef RCPP_SUGAR_NONA_NONA_H
#define RCPP_SUGAR_NONA_NONA_H

namespace Rcpp{
    namespace sugar {     
    
        template <typename Expr>
        class Nona : 
            public SugarVectorExpression<Nona<Expr>>, 
            public custom_sugar_vector_expression 
        {
        public:
            // TODO: do something to mark for the no NA property
            typedef typename Expr::value_type value_type ;
    
            Nona( const SugarVectorExpression<Expr>& expr) : data(expr.get_ref()){} 
            
            inline R_xlen_t size() const { return data.size() ; }
            inline value_type operator[](R_xlen_t i) const { return data[i] ; }
            
            template <typename Target>
            void apply( Target& target ){
                data.get_ref().apply(target) ;  
            }
            
        private:
            const SugarVectorExpression<Expr>& data ;    
        } ;
        
    }
    
    template <typename Expr>
    inline sugar::Nona<Expr> noNA( const SugarVectorExpression<Expr>& vec ){
        return sugar::Nona<Expr>( vec ) ;
    }

}

#endif
