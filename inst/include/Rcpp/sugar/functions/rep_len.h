#ifndef Rcpp__sugar__rep_len_h
#define Rcpp__sugar__rep_len_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Rep_len :
            public SugarVectorExpression<Rep_len<Expr>>,
            public custom_sugar_vector_expression {
        
        public:
            typedef typename Expr::value_type value_type ;
            
            Rep_len( const VEC_TYPE& object_, R_xlen_t len_ ) :
                object(object_), len(len_), n(object_.size()){}
        
            inline value_type operator[]( R_xlen_t i ) const {
                return object[ i % n ] ;
            }
            inline R_xlen_t size() const { return len ; }
        
            template <typename Target>
            inline void apply(Target& target) const {
                if (n >= len) {
                    std::copy_n(sugar_begin(*this), len, target.begin() );
                    return;
                }
        
                int timesToFullCopy = len / n;
                int leftoverElems = len % n;
                
                // first copy data from the sugar expression
                auto it = target.begin();
                std::copy_n(sugar_begin(*this), n, it);
                it += n;
                        
                // then copy the materialized part into the rest of the output
                for (R_xlen_t i=1; i < timesToFullCopy; ++i) {
                    std::copy_n(target.begin(), n, it);
                    it += n;
                    
                }
                if (leftoverElems) {
                    std::copy_n(target.begin(), leftoverElems, it);
                }
                
            }
        
        private:
            const SugarVectorExpression<Expr>& object ;
            R_xlen_t len, n ;
        
        } ;
    
    } // sugar
    
    template <typename Expr>
    inline sugar::Rep_len<Expr> rep_len( const SugarVectorExpression<Expr>& t, R_xlen_t len ){
        return sugar::Rep_len<Expr>( t, len ) ;
    }


} // Rcpp
#endif

