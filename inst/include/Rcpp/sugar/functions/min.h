#ifndef Rcpp__sugar__min_h
#define Rcpp__sugar__min_h

namespace Rcpp{
    namespace sugar{

        template <typename Expr, typename STORAGE>
        class Min {
        public:
            Min( const SugarVectorExpression<Expr>& obj_) : obj(obj_) {}
            
            operator STORAGE() {
                auto it = sugar_begin(obj) ;
                STORAGE min_ = *it ;
                if( min_ == NA ) return min_ ;
                ++it ;
                
                R_xlen_t n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++, ++it ){
                    STORAGE current = *it ;
                    if( current == NA ) return current;
                    if( current < min_ ) min_ = current ;
                }
                return min_ ;
            }
            
        private:
            const SugarVectorExpression<Expr>& obj ;
        } ;
        
    } // sugar
    
    template <typename Expr>
    typename Expr::value_type min( const SugarVectorExpression<Expr>& x){
        return sugar::Min<Expr, typename Expr::value_type>(x.get_ref()) ;
    }

} // Rcpp

#endif
