#ifndef Rcpp__sugar__head_h
#define Rcpp__sugar__head_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Head : 
            public SugarVectorExpression<eT, Head<eT,Expr>>, 
            public custom_sugar_vector_expression 
        {
        public:
            Head( const SugarVectorExpression<eT,Expr>& object_, R_xlen_t n_ ) : object(object_), n(n_) {
                if( n < 0 ){
                    n = object.size() + n ;
                }
            }
        
            inline eT operator[]( R_xlen_t i ) const {
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
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t n ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Head<eT, Expr> head( const SugarVectorExpression<RTYPE,Expr>& t,R_xlen_t n ){
        return sugar::Head<eT, Expr>( t, n ) ;
    }

} // Rcpp
#endif

