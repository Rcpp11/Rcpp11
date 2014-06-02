#ifndef Rcpp__sugar__diff_h
#define Rcpp__sugar__diff_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct diff_op {
            inline T operator()(T x, T y){ 
                if( x == NA || y == NA ) return NA ;
                return x - y ;
            }        
        } ;
        
        template <>
        struct diff_op<double>{
            inline double operator()(double x, double y){ 
                return x - y ; 
            }    
        } ;
        
        
        template <typename Expr>
        class Diff : public SugarVectorExpression<Diff<Expr>> {
        public:
            typedef typename Expr::value_type value_type ;
            typedef Vector< traits::r_sexptype_traits<value_type>::rtype > Vec ;
            
            Diff( const SugarVectorExpression<Expr>& lhs ) : data(lhs.size()-1) {
                int n = lhs.size()-1 ;
                value_type previous = lhs[0] ;
                auto it = data.begin() ;
                for( int i=0; i<n; i++, ++it){
                    value_type current = lhs[i+1] ;
                    *it      =  diff_op<value_type>(current, previous);
                    previous = current ;
                }
                
            }
        
            inline value_type operator[]( R_xlen_t i ) const {
                return data[i] ;
            }     
        
            inline R_xlen_t size() const {
                return data.size() ; 
            }
            
            template <typename Target>
            void apply( Target& target ){
                target = data ;        
            }
        
        private:
            Vec data ;
        } ;
        
    } // sugar
    
    template <typename Expr>
    inline sugar::Diff<Expr> diff( const SugarVectorExpression<Expr>& lhs ){
        return sugar::Diff<Expr>( lhs ) ;
    }
    
} // Rcpp
#endif

