#ifndef Rcpp__sugar__range_h
#define Rcpp__sugar__range_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Range {
        public:
            typedef typename traits::vector_of<eT>::type Vector ;
            
            Range( const SugarVectorExpression<eT,Expr>& obj_) : obj(obj_) {}
            
            inline Vector get() const {
                auto it = sugar_begin(obj) ;
                min_ = max_ = *it ;
                if( min_ == NA ) return Vector::create( min_, max_ ) ;
                ++it ;
                
                int n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++, ++it){
                    current = *it ;
                    if( current == NA ) return Vector::create( min_, max_ ) ;
                    if( current < min_ ) min_ = current ;
                    if( current > max_ ) max_ = current ;
                }
                return Vector::create( min_, max_ ) ;
            }
            
            
        private:
            const SugarVectorExpression<eT,Expr>& obj ;
            eT min_, max_, current ;
        } ;
         
    
    } // sugar
    
    template <typename eT, typename Expr>
    typename traits::vector_of<eT>::type range( const SugarVectorExpression<eT,Expr>& x){
        return sugar::Range<eT,Expr>(x).get() ;
    }

} // Rcpp

#endif
