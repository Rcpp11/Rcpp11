#ifndef Rcpp__sugar__mean_h
#define Rcpp__sugar__mean_h

namespace Rcpp{
    namespace sugar{
    
        // REALSXP
        template <typename Expr, typename T>
        class Mean ;
        
        template <typename Expr>
        class Mean<Expr,double> {
        public:
            
            Mean( const SugarVectorExpression<Expr>& object_ ) : object(object_){}
            
            double get() const {
                NumericVector input = object ;
                
                // double pass (as in summary.c)
                int n = input.size() ;
                long double s = std::accumulate( input.begin(), input.end(), 0.0L ) ;
                s /= n ;
                if(R_FINITE((double)s)) {  
                    long double t = std::accumulate( input.begin(), input.end(), 0.0L, [&s](double res, double v){
                            return res + (v-s) ;
                    }); 
                    s += t/n;
                }
                return (double)s ;
            }
            
        private:
            const SugarVectorExpression<Expr>& object ;
        };
          
        // CPLXSXP
        template <typename Expr> 
        class Mean<Expr, Rcomplex>{
        public:
            Mean_Complex( const SugarVectorExpression<Expr>& object_ ) : object(object_){}
            
            Rcomplex get() const {
                ComplexVector input = object ;
                
                // double pass (as in summary.c)
                long double n = input.size() ;
                long double re = 0.0, im = 0.0 ; 
                std::for_each( input.begin(), input.end(), [&](Rcomplex x){
                        re += x.r ;
                        im += x.i ;
                }) ;
                re /= n ;
                im /= n ;
                
                long double t_re = 0.0, t_im = 0.0 ;
                if( R_FINITE((double)re ) && R_FINITE((double)im ) ) {  
                    std::for_each( input.begin(), input.begin(), [&](Rcomplex x){
                            t_re += (x.r - re) ;
                            t_im += (x.i - im) ;
                    }); 
                    re += t_re / n ;
                    im += t_im / n ;
                }
                return Rcomplex{ (double)re, (double)im } ;
            }
            
        private:
            // we resolve the data since we need to make two passes
            const SugarVectorExpression<Expr>& object ;
        };
        
        // INTSXP
        template <typename Expr> 
        class Mean<Expr, int>{
        public:
            
            Mean( const SugarVectorExpression<Expr>& object_ ) : object(object_){}
            
            double get() const {
                IntegerVector input = object ;
                R_xlen_t n = input.size() ;
                long double s = 0.0L ;
                for( R_xlen_t i=0; i<n; i++){
                    if( input[i] == NA ) return NA ;
                    s += input[i] ;
                }
                s /= n ;
                return (double)s ;
            }
            
        private:
            // we resolve the data since we need to make two passes
            const SugarVectorExpression<Expr>& object ;
        };
        
        // LGLSXP
        template <typename Expr> 
        class Mean<Expr, Rboolean>{
        public:
            
            Mean( const SugarVectorExpression<Expr>& object_ ) : object(object_){}
            
            double get() const {
                LogicalVector input = object ;
                R_xlen_t n = input.size() ;
                long double s = 0.0L ;
                for( R_xlen_t i=0; i<n; i++){
                    if( input[i] == NA ) return NA ;
                    s += input[i] ;
                }
                s /= n ;
                return (double)s ;
            }
            
        private:
            // we resolve the data since we need to make two passes
            const SugarVectorExpression<Expr>& object ;
        };
        
        
    } // sugar
    
    template <typename Expr>
    inline auto mean( const SugarVectorExpression<Expr>& t) -> decltype(sugar::Mean<Expr,typename Expr::value_type>(t).get()) {
        return sugar::Mean<Expr,typename Expr::value_type>(t).get() ;
    }
    
} // Rcpp
#endif

