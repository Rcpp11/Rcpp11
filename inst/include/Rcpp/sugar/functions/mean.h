#ifndef Rcpp__sugar__mean_h
#define Rcpp__sugar__mean_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Mean ;
        
        // REALSXP
        template <typename Expr>
        class Mean<double,Expr> {
        public:
            
            Mean( const SugarVectorExpression<double,Expr>& object_ ) : object(object_){}
            
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
            const SugarVectorExpression<double,Expr>& object ;
        };
          
        // CPLXSXP
        template <typename Expr> 
        class Mean<Rcomplex,Expr>{
        public:
            Mean_Complex( const SugarVectorExpression<Rcomplex,Expr>& object_ ) : object(object_){}
            
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
            const SugarVectorExpression<Rcomplex,Expr>& object ;
        };
        
        // INTSXP
        template <typename Expr> 
        class Mean<int, Expr>{
        public:
            
            Mean( const SugarVectorExpression<int,Expr>& object_ ) : object(object_){}
            
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
            const SugarVectorExpression<int,Expr>& object ;
        };
        
        // LGLSXP
        template <typename Expr> 
        class Mean<Rboolean, Expr>{
        public:
            
            Mean( const SugarVectorExpression<Rboolean, Expr>& object_ ) : object(object_){}
            
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
            const SugarVectorExpression<Rboolean,Expr>& object ;
        };
        
        
    } // sugar
    
    template <typename eT, typename Expr>
    inline auto mean( const SugarVectorExpression<eT,Expr>& t) -> decltype(sugar::Mean<eT,Expr>(t).get()) {
        return sugar::Mean<eT,Expr>(t).get() ;
    }
    
} // Rcpp
#endif

