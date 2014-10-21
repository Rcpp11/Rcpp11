#ifndef RCPP_SUGAR_NONA_NONA_H
#define RCPP_SUGAR_NONA_NONA_H

namespace Rcpp{
    namespace sugar {     
    
        template <typename eT, typename Expr>
        class Nona : 
            public SugarVectorExpression<eT, Nona<eT, Expr>>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef typename Expr::const_iterator const_iterator ; 
            
            Nona( const SugarVectorExpression<eT, Expr>& expr) : data(expr){} 
            
            inline R_xlen_t size() const { return data.size() ; }
            inline eT operator[](R_xlen_t i) const { return data[i] ; }
            
            template <typename Target>
            void apply( Target& target ){
                data.get_ref().apply(target) ;  
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                data.get_ref().apply_parallel(target) ;    
            }
    
            
            inline const_iterator begin() const { return sugar_begin(data) ; }
            inline const_iterator end() const { return sugar_end(data) ; }
            
        private:
            const SugarVectorExpression<eT, Expr>& data ;    
        } ;
        
    }
    
    template <typename eT, typename Expr>
    inline sugar::Nona<eT, Expr> noNA( const SugarVectorExpression<eT, Expr>& vec ){
        return sugar::Nona<eT, Expr>( vec ) ;
    }

}

#endif
