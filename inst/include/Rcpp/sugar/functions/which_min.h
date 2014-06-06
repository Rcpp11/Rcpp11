#ifndef Rcpp__sugar__which_min_h
#define Rcpp__sugar__which_min_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class WhichMin {
        public:
            WhichMin(const SugarVectorExpression<eT, Expr>& obj_ ) : obj(obj_){}
        
            int get() const {
                eT current = obj[0] ;
                eT min = current ;
                R_xlen_t index = 0 ;
                if( current == NA ) return NA ;
                R_xlen_t n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++){
                    current = obj[i] ;
                    if( current == NA ) return NA ;
                    if( current < min ){
                        min = current ;
                        index = i ;
                    }
                }
                return index ;
            }
        
        private:
            const SugarVectorExpression<eT, Expr>& obj ;
        
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr>
    int which_min( const SugarVectorExpression<eT, Expr>& t ){
        return sugar::WhichMin<eT, Expr>(t).get() ; 
    }
  
} // Rcpp

#endif

