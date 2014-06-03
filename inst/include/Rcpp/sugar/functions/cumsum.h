#ifndef Rcpp__sugar__cumsum_h
#define Rcpp__sugar__cumsum_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Cumsum : 
            public SugarVectorExpression<eT,Cumsum<eT,Expr>>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef typename traits::vector_of<eT>::type VECTOR ;
        
            Cumsum( const SugarVectorExpression<eT, Expr>& object ) : data(object.size(), NA){
                int n = object.size() ;
                eT current = object[0] ;
                if( current != NA ){
                    data[0] = current ;
                    for( R_xlen_t i=1; i<n ; i++){
                        current = object[i] ;
                        if( current == NA ) break ;
                        data[i] = data[i-1] + current ;
                    }
                }
            }
        
            inline R_xlen_t size() const {
                return data.size() ;    
            }
            
            inline eT operator[]( R_xlen_t i) const {
                return data[i] ;    
            }
            
            template <typename Target>
            void apply( Target& target ){ 
                target = data ;    
            }
            
        private:
            VECTOR data ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Cumsum<eT,Expr> cumsum( const SugarVectorExpression<eT, Expr>& t){
        return sugar::Cumsum<eT, Expr>( t ) ;
    }
    
} // Rcpp
#endif

