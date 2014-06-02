#ifndef Rcpp__sugar__rev_h
#define Rcpp__sugar__rev_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Rev : 
            public SugarVectorExpression<Rev<Expr>>, 
            public custom_sugar_vector_expression {
        public:
            typedef typename Expr::value_type value_type ;
            
            Rev( const SugarVectorExpression<Expr>& object_ ) : 
                object(object_), n(object_.size()) {}
        
            inline STORAGE operator[]( R_xlen_t i ) const {
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
            const SugarVectorExpression<Expr>& object ;
            R_xlen_t n ;
        } ;
    
    } // sugar
    
    template <typename Expr>
    inline sugar::Rev<Expr> rev( const SugarVectorExpression<Expr>& t){
        return sugar::Rev<Expr>( t ) ;
    }

} // Rcpp
#endif

