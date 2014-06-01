#ifndef Rcpp__sugar__head_h
#define Rcpp__sugar__head_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Head : 
            public SugarVectorExpression<Head<Expr>>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef typename Expr::value_type value_type ;
        
            Head( const Expr& object_, R_xlen_t n_ ) : object(object_), n(n_) {
                if( n < 0 ){
                    n = object.size() + n ;
                }
            }
        
            inline value_type operator[]( R_xlen_t i ) const {
                return object[ i ] ;
            }
            inline R_xlen_t size() const { 
                return n; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::copy_n( sugar_begin(object), n, target.begin() ) ;   
            }
            
        private:
            const Expr& object ;
            R_xlen_t n ;
        } ;
    
    } // sugar
    
    template <typename Expr>
    inline sugar::Head<Expr> head( 
        const SugarVectorExpression<Expr>& t, 
        R_xlen_t n 
        ){
        return sugar::Head<Expr>( t, n ) ;
    }

} // Rcpp
#endif

