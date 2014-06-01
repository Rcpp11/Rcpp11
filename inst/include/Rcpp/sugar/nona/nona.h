#ifndef RCPP_SUGAR_NONA_NONA_H
#define RCPP_SUGAR_NONA_NONA_H

namespace Rcpp{
    namespace sugar {     
    
        template <typename Expr>
        class Nona : public SugarVectorExpression<Nona<Expr>> {
        public:
            typedef typename Expr::value_type value_type ;
    
            Nona( const Expr& expr) : data(expr.get_ref()){} 
            
            inline R_xlen_t size() const { return data.size() ; }
            inline STORAGE operator[](R_xlen_t i) const { return data[i] ; }
            
            template <typename Target>
            void apply( Target& target ){
                data.apply(target) ;  
            }
            
        private:
            const Expr& data ;    
        } ;
        
    }
    
    template <typename Expr>
    inline sugar::Nona<Expr> noNA( const SugarVectorExpression<Expr>& vec ){
        return sugar::Nona<Expr>( vec ) ;
    }

}

#endif
