#ifndef Rcpp__sugar__min_h
#define Rcpp__sugar__min_h

namespace Rcpp{
    namespace sugar{

        template <typename eT, typename Expr>
        class Min {
        public:
            Min( const SugarVectorExpression<eT,Expr>& obj_) : obj(obj_) {}
            
            inline eT get() const {
                auto it = sugar_begin(obj) ;
                eT min_ = *it ;
                if( min_ == NA ) return min_ ;
                ++it ;
                
                R_xlen_t n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++, ++it ){
                    eT current = *it ;
                    if( current == NA ) return current;
                    if( current < min_ ) min_ = current ;
                }
                return min_ ;
            }
            
        private:
            const SugarVectorExpression<eT,Expr>& obj ;
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr>
    eT min( const SugarVectorExpression<eT,Expr>& x){
        return sugar::Min<eT, Expr>(x) ;
    }

} // Rcpp

#endif
