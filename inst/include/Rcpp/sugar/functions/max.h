#ifndef Rcpp__sugar__max_h
#define Rcpp__sugar__max_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr, typename STORAGE>
        class Max {
        public:
            Max( const SugarVectorExpression<Expr>& obj_) : obj(obj_) {}
            
            operator STORAGE() {
                auto it = sugar_begin(obj) ;
                STORAGE max_ = *it ;
                if( max_ == NA ) return max_ ;
                ++it ;
                
                R_xlen_t n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++, ++it ){
                    STORAGE current = *it ;
                    if( current == NA ) return current;
                    if( current > max_ ) max_ = current ;
                }
                return max_ ;
            }
            
        private:
            const SugarVectorExpression<Expr>& obj ;
        } ;
        
    } // sugar
    
    template <typename Expr>
    typename Expr::value_type max( const SugarVectorExpression<Expr>& x){
        return sugar::Max<Expr, typename Expr::value_type>(x.get_ref()) ;
    }

} // Rcpp

#endif
