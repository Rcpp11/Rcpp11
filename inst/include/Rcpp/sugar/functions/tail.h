#ifndef Rcpp__sugar__tail_h
#define Rcpp__sugar__tail_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Tail : 
            public SugarVectorExpression<eT,Tail<eT,Expr>>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef typename Expr::const_iterator const_iterator ;
            
            Tail( const SugarVectorExpression<eT,Expr>& object_, R_xlen_t n_ ) : object(object_), start(0), n(n_) {
                if( n > 0 ){
                    start = object.size() - n ;
                } else {
                    start = -n ;
                    n = object.size() - start ;
                }
            }
        
            inline R_xlen_t size() const { return n; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::copy_n( sugar_begin(object) + start, n, target.begin() ) ; 
            }
            
            inline const_iterator begin() const { return sugar_begin(object) + start ; }
            inline const_iterator end() const { return begin() + size() ; }
            
        private:
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t start, n ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Tail<eT, Expr> tail( const SugarVectorExpression<eT, Expr>& t, R_xlen_t n ){
        return sugar::Tail<eT, Expr>( t, n ) ;
    }

} // Rcpp
#endif

