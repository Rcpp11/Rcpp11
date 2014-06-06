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
            typedef typename VECTOR::const_iterator const_iterator ;
        
            Cumsum( const SugarVectorExpression<eT, Expr>& object ) : data(object.size(), NA){
                int n = object.size() ;
                auto it = sugar_begin(object) ;
                eT current = *it ; ++it ;
                if( current != NA ){
                    data[0] = current ;
                    for( R_xlen_t i=1; i<n ; i++, ++it){
                        current = *it ;
                        if( current == NA ) break ;
                        data[i] = data[i-1] + current ;
                    }
                }
            }
        
            inline R_xlen_t size() const {
                return data.size() ;    
            }
            
            template <typename Target>
            void apply( Target& target ) const { 
                target = data ;    
            }
            
            inline const_iterator begin() const { return data.begin() ; }
            inline const_iterator end() const { return data.end() ; }
            
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

