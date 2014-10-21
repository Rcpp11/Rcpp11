#ifndef Rcpp__sugar__diff_h
#define Rcpp__sugar__diff_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct diff_op {
            inline T operator()(T x, T y) const { 
                if( x == NA || y == NA ) return NA ;
                return x - y ;
            }        
        } ;
        
        template <>
        struct diff_op<double>{
            inline double operator()(double x, double y) const { 
                return x - y ; 
            }    
        } ;
        
        
        template <typename eT, typename Expr>
        class Diff : public SugarVectorExpression<eT, Diff<eT, Expr>> {
        public:
            typedef typename traits::vector_of<eT>::type Vec ;
            typedef typename Vec::const_iterator const_iterator ;
            
            Diff( const SugarVectorExpression<eT,Expr>& lhs ) : data(lhs.size()-1) {
                int n = lhs.size()-1 ;
                auto source = sugar_begin(lhs) ;
                eT previous = *source ;
                auto it = data.begin() ;
                diff_op<eT> op ;
                ++source ;
                for( int i=0; i<n; i++, ++it, ++source){
                    eT current = *source ;
                    *it        = op(current, previous);
                    previous   = current ;
                }
                
            }
        
            inline R_xlen_t size() const {
                return data.size() ; 
            }
            
            template <typename Target>
            void apply( Target& target ) const {
                target = data ;        
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                apply(target) ;
            }
            
            template <typename Target>
            inline void apply_serial( Target& target ) const {
                apply(target) ;
            }
            
            inline const_iterator begin() const { return data.begin() ; }
            inline const_iterator end() const { return data.end() ; }
            
        private:
            Vec data ;
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Diff<eT,Expr> diff( const SugarVectorExpression<eT,Expr>& lhs ){
        return sugar::Diff<eT,Expr>( lhs ) ;
    }
    
} // Rcpp
#endif

