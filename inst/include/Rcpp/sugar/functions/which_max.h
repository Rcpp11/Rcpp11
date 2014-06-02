#ifndef Rcpp__sugar__which_max_h
#define Rcpp__sugar__which_max_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class WhichMax {
        public:
            typedef typename Expr::value_type STORAGE ;
            
            WhichMax(const SugarVectorExpression<Expr>& obj_ ) : obj(obj_){}
        
            int get() const {
                STORAGE current = obj[0] ;
                STORAGE max = current ;
                R_xlen_t index = 0 ;
                if( current == NA ) return NA ;
                R_xlen_t n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++){
                    current = obj[i] ;
                    if( current == NA ) return NA ;
                    if( current > max ){
                        max = current ;
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
    int which_max( const SugarVectorExpression<Expr>& t ){
        return sugar::WhichMax<Expr>(t).get() ; 
    }
  
} // Rcpp

#endif

