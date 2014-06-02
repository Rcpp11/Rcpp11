#ifndef Rcpp__sugar__tail_h
#define Rcpp__sugar__tail_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Tail : 
            public SugarVectorExpression<Tail<Expr>>, 
            public custom_sugar_vector_expression {
        public:
            typedef typename Expr::value_type value_type ;
            
            Tail( const SugarVectorExpression<Expr>& object_, R_xlen_t n_ ) : object(object_), start(0), n(n_) {
                if( n > 0 ){
                    start = object.size() - n ;
                } else {
                    start = -n ;
                    n = object.size() - start ;
                }
            }
        
            inline value_type operator[]( R_xlen_t i ) const {
                return object[ start + i ] ;
            }
            inline R_xlen_t size() const { return n; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::copy_n( sugar_begin(object) + start, n, target.begin() ) ; 
            }
            
        private:
            const SugarVectorExpression<Expr>& object ;
            R_xlen_t start, n ;
        } ;
    
    } // sugar
    
    template <typename Expr>
    inline sugar::Tail<Expr> tail( const SugarVectorExpression<Expr>& t, R_xlen_t n ){
        return sugar::Tail<Expr>( t, n ) ;
    }

} // Rcpp
#endif

