#ifndef Rcpp__sugar__cumsum_h
#define Rcpp__sugar__cumsum_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Cumsum : 
            public SugarVectorExpression<Cumsum<Expr>>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef typename Expr::value_type value_type ;
            typedef Rcpp::Vector<Rcpp::traits::r_sexptype_traits<value_type>::rtype> VECTOR ;
        
            Cumsum( const VEC_TYPE& object ) : data(object.size(), NA){
                int n = object.size() ;
                STORAGE current = object[0] ;
                if( current != NA ){
                    data[0] = current ;
                    for( R_xlen_t i=1; i<n && ; i++){
                        current = object[i] ;
                        if( current == NA ) break ;
                        data[i] = result[i-1] + current ;
                    }
                }
            }
        
            inline R_xlen_t size() const {
                return data.size() ;    
            }
            
            inline value_type operator[]( R_xlen_t i) const {
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
    
    template <typename Expr>
    inline sugar::Cumsum<Expr> cumsum( const SugarVectorExpression<Expr>& t){
        return sugar::Cumsum<Expr>( t ) ;
    }
    
} // Rcpp
#endif

