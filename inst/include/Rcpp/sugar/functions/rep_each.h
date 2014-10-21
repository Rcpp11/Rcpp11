#ifndef Rcpp__sugar__rep_each_h
#define Rcpp__sugar__rep_each_h

namespace Rcpp{
    namespace sugar{
    
       template <typename eT, typename Expr>
        class Rep_each :
            public SugarVectorExpression<eT, Rep_each<eT,Expr>>,
            public custom_sugar_vector_expression
        {
        public:
            typedef each_iterator<eT, typename Expr::const_iterator> const_iterator ;
            
            Rep_each( const SugarVectorExpression<eT,Expr>& object_, int times_ ) :
                object(object_), times(times_), n(object_.size()) {}
        
            inline R_xlen_t size() const { return n * times ; }
        
            template <typename Target>
            inline void apply(Target& target) const {
                apply_serial(target) ;
            }
            
            template <typename Target>
            inline void apply_serial(Target& target) const {
                auto it = target.begin();
                auto source_it = sugar_begin(object) ;
                for (R_xlen_t i=0; i < n; ++i, it += times, ++source_it) {
                    std::fill(it, it + times, *source_it);
                }
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                apply_serial(target) ;    
            }
        
            inline const_iterator begin() const { 
                return const_iterator( sugar_begin(object), 0, times ) ; 
            }
            inline const_iterator end() const { 
                return const_iterator( sugar_begin(object), size(), times ) ; 
            }
            
        private:
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t times, n ;
        
        } ;
    
    }
    
    template <typename eT, typename Expr>
    inline sugar::Rep_each<eT, Expr> rep_each( const SugarVectorExpression<eT,Expr>& t, R_xlen_t times ){
        return sugar::Rep_each<eT,Expr>( t, times ) ;
    }

}
#endif

