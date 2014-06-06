#ifndef Rcpp__sugar__which_max_h
#define Rcpp__sugar__which_max_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class WhichMax {
        public:
            WhichMax(const SugarVectorExpression<eT, Expr>& obj_ ) : obj(obj_){}
        
            int get() const {
                eT current = obj[0] ;
                eT max = current ;
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
            const SugarVectorExpression<eT, Expr>& obj ;
        
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr>
    int which_max( const SugarVectorExpression<eT, Expr>& t ){
        return sugar::WhichMax<eT, Expr>(t).get() ; 
    }
  
} // Rcpp

#endif

