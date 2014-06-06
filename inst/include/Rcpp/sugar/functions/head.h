#ifndef Rcpp__sugar__head_h
#define Rcpp__sugar__head_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Head : 
            public SugarVectorExpression<eT, Head<eT,Expr>>
        {
        public:
            typedef typename Expr::const_iterator const_iterator ;
            
            Head( const SugarVectorExpression<eT,Expr>& object_, R_xlen_t n_ ) : object(object_), n(n_) {
                if( n < 0 ){
                    n = object.size() + n ;
                }
            }
        
            inline R_xlen_t size() const { 
                return n; 
            }
        
            inline const_iterator begin() const { return sugar_begin(object) ; }
            inline const_iterator end() const { return begin() + n ; }
            
        private:
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t n ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Head<eT, Expr> head( const SugarVectorExpression<eT,Expr>& t,R_xlen_t n ){
        return sugar::Head<eT, Expr>( t, n ) ;
    }

} // Rcpp
#endif

