#ifndef Rcpp__sugar__sum_h
#define Rcpp__sugar__sum_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        inline T get_zero(){
            return static_cast<T>(0) ;
        }
        template <>
        inline Rcomplex get_zero<Rcomplex>(){
            Rcomplex cx = {0.0,0.0};
            return cx ;
        }
        
        template <typename Expr>
        class Sum {
        public:
            typedef typename Expr::value_type value_type ;
            
            Sum( const SugarVectorExpression<Expr>& object_ ) : object(object_){}
        
            value_type get() const {
                value_type result = get_zero<value_type>() ;
                R_xlen_t n = object.size() ;
                value_type current ;
                auto it = sugar_begin(object) ;
                for( R_xlen_t i=0; i<n; i++, ++it){
                    current = *it ;
                    if( current == NA ) 
                        return NA ;
                    result += current ;
                }
                return result ;
            }         
        private:
            const SugarVectorExpression<Expr>& object ;
        } ;
       
    } // sugar
    
    template <typename Expr>
    inline sugar::Sum<Expr> sum( const SugarVectorExpression<Expr>& t){
        return sugar::Sum<Expr>( t ) ;
    }
    
} // Rcpp
#endif

