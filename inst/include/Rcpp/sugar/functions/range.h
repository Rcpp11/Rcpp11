#ifndef Rcpp__sugar__range_h
#define Rcpp__sugar__range_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Range {
        public:
            typedef typename Expr::value_type STORAGE ;
            const static int RTYPE = traits::r_sexptype_traits<STORAGE>::rtype ; 
            
            Range( const SugarVectorExpression<Expr>& obj_) : obj(obj_) {}
            
            operator Vector<RTYPE>(){
                auto it = sugar_begin(obj) ;
                min_ = max_ = *it ;
                if( min_ == NA ) return Vector<RTYPE>::create( min_, max_ ) ;
                ++it ;
                
                int n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++, ++it){
                    current = *it ;
                    if( current == NA ) return Vector<RTYPE>::create( min_, max_ ) ;
                    if( current < min_ ) min_ = current ;
                    if( current > max_ ) max_ = current ;
                }
                return Vector<RTYPE>::create( min_, max_ ) ;
            }
            
            
        private:
            const SugarVectorExpression<Expr>& obj ;
            STORAGE min_, max_, current ;
        } ;
         
    
    } // sugar
    
    template <typename Expr>
    typename traits::vector_of<typename Expr::value_type>::type range( const SugarVectorExpression<Expr>& x){
        return sugar::Range<Expr>(x) ;
    }

} // Rcpp

#endif
