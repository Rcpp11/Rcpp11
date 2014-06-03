#ifndef Rcpp__sugar__max_h
#define Rcpp__sugar__max_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Max {
        public:
            Max( const SugarVectorExpression<eT, Expr>& obj_) : obj(obj_) {}
            
            inline eT get() {
                auto it = sugar_begin(obj) ;
                eT max_ = *it ;
                if( max_ == NA ) return max_ ;
                ++it ;
                
                R_xlen_t n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++, ++it ){
                    eT current = *it ;
                    if( current == NA ) return current;
                    if( current > max_ ) max_ = current ;
                }
                return max_ ;
            }
            
        private:
            const SugarVectorExpression<eT, Expr>& obj ;
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr>
    eT max( const SugarVectorExpression<eT, Expr>& x){
        return sugar::Max<eT, Expr>(x).get() ;
    }

} // Rcpp

#endif
