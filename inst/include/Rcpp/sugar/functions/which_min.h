#ifndef Rcpp__sugar__which_min_h
#define Rcpp__sugar__which_min_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class WhichMin {
        public:
            typedef typename Expr::value_type STORAGE ;
            
            WhichMin(const SugarVectorExpression<Expr>& obj_ ) : obj(obj_){}
        
            int get() const {
                STORAGE current = obj[0] ;
                STORAGE min = current ;
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
            const SugarVectorExpression<Expr>& obj ;
        
        } ;
        
    } // sugar
    
    template <typename Expr>
    int which_min( const SugarVectorExpression<Expr>& t ){
        return sugar::WhichMin<Expr>(t).get() ; 
    }
  
} // Rcpp

#endif

