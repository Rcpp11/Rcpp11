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
        
        template <typename Expr>
        class Sum<Rboolean,Expr> {
        public:
            Sum( const SugarVectorExpression<Rboolean,Expr>& object_ ) : object(object_){}
        
            int get() const {
                int result = 0 ;
                for( Rboolean current: object.get_ref() ){
                    switch( current ){
                        case TRUE: 
                            {
                                result++; 
                                break ;
                            }
                        case NA_VALUE: return NA ;
                        default: break ;
                    }
                }
                return result ;
            }         
        private:
            const SugarVectorExpression<Rboolean,Expr>& object ;
        } ;
       
    } // sugar
    
    template <typename eT, typename Expr>
    inline auto sum( const SugarVectorExpression<eT, Expr>& t) -> decltype(sugar::Sum<eT, Expr>( t ).get()){
        return sugar::Sum<eT, Expr>( t ).get() ;
    }
    
} // Rcpp
#endif

