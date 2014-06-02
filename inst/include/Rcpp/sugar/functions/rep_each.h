#ifndef Rcpp__sugar__rep_each_h
#define Rcpp__sugar__rep_each_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Rep_each :
            public SugarVectorExpression<Rep_each<Expr>>,
            public custom_sugar_vector_expression {
        
        public:
            typedef typename Expr::value_type value_type ;
            
            Rep_each( const SugarVectorExpression<Expr>& object_, int times_ ) :
                object(object_), times(times_), n(object_.size()) {}
        
            inline value_type operator[]( R_xlen_t i ) const {
                return object[ i / times ] ;
            }
            inline R_xlen_t size() const { return n * times ; }
        
            template <typename Target>
            inline void apply(Target& target) const {
                auto it = target.begin();
                auto source_it = sugar_begin(object) ;
                for (R_xlen_t i=0; i < n; ++i, it += times, ++source_it) {
                    std::fill(it, it + times, *source_it);
                }
            }
        
        private:
            const SugarVectorExpression<Expr>& object ;
            R_xlen_t times;
            R_xlen_t n ;
        
        } ;
    
    }
    
    template <typename Expr>
    inline sugar::Rep_each<Expr> rep_each( const SugarVectorExpression<Expr>& t, R_xlen_t times ){
        return sugar::Rep_each<Expr>( t, times ) ;
    }

}
#endif

