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
        
        template <typename eT, typename Expr>
        class Sum {
        public:
            Sum( const SugarVectorExpression<eT,Expr>& object_ ) : object(object_){}
        
            eT get() const {
                eT result = get_zero<eT>() ;
                R_xlen_t n = object.size() ;
                eT current ;
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
            const SugarVectorExpression<eT,Expr>& object ;
        } ;
       
    } // sugar
    
    template <typename eT, typename Expr>
    inline eT sum( const SugarVectorExpression<eT, Expr>& t){
        return sugar::Sum<eT, Expr>( t ).get() ;
    }
    
} // Rcpp
#endif

