#ifndef Rcpp__sugar__rev_h
#define Rcpp__sugar__rev_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Rev : 
            public SugarVectorExpression<eT, Rev<eT,Expr>>, 
            public custom_sugar_vector_expression {
        public:
            Rev( const SugarVectorExpression<eT,Expr>& object_ ) : 
                object(object_), n(object_.size()) {}
        
            inline eT operator[]( R_xlen_t i ) const {
                return object[n - i - 1] ;
            }
            inline R_xlen_t size() const { 
                return n ; 
            }
               
            template <typename Target>
            inline void apply( Target& target ) const {
                auto source_it=sugar_begin(object) ;
                auto it = target.end() ;
                for( R_xlen_t i=0; i<n; i++, ++source_it) { 
                    *(--it) = *source_it ;
                }
            }
            
        private:
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t n ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Rev<eT, Expr> rev( const SugarVectorExpression<eT, Expr>& t){
        return sugar::Rev<eT, Expr>( t ) ;
    }

} // Rcpp
#endif

