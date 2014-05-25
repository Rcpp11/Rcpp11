#ifndef Rcpp__sugar__mean_h
#define Rcpp__sugar__mean_h

namespace Rcpp{
    namespace sugar{
    
        // REALSXP
        template <bool NA, typename T> 
        class Mean_Numeric : Lazy<double, Mean_Numeric<NA,T> >{
        public:
            typedef SugarVectorExpression<REALSXP,NA,T> VEC_TYPE ;
            
            Mean_Numeric( const VEC_TYPE& object_ ) : object(object_){}
            
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
            // we resolve the data since we need to make two passes
            const VEC_TYPE& object ;
        };
          
        // CPLXSXP
        template <bool NA, typename T> 
        class Mean_Complex : public Lazy< Rcomplex, Mean_Complex<NA,T> >{
        public:
            typedef SugarVectorExpression<CPLXSXP,NA,T> VEC_TYPE ;
            
            Mean_Complex( const VEC_TYPE& object_ ) : object(object_){}
            
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
            const VEC_TYPE& object ;
        };
        
        // INTSXP
        template <int RTYPE, bool HAS_NA, typename T> 
        class Mean_Integer : Lazy<double, Mean_Integer<RTYPE,HAS_NA,T> >{
        public:
            typedef SugarVectorExpression<INTSXP,HAS_NA,T> VEC_TYPE ;
            
            Mean_Integer( const VEC_TYPE& object_ ) : object(object_){}
            
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
            const VEC_TYPE& object ;
        };
        
        
    } // sugar
    
    template <bool NA, typename T>
    inline sugar::Mean_Numeric<NA,T> mean( const SugarVectorExpression<REALSXP,NA,T>& t){
        return sugar::Mean_Numeric<NA,T>( t ) ;
    }

    template <bool NA, typename T>
    inline sugar::Mean_Complex<NA,T> mean( const SugarVectorExpression<CPLXSXP,NA,T>& t){
        return sugar::Mean_Complex<NA,T>( t ) ;
    }

    template <bool NA, typename T>
    inline sugar::Mean_Integer<INTSXP,NA,T> mean( const SugarVectorExpression<INTSXP,NA,T>& t){
        return sugar::Mean_Integer<INTSXP,NA,T>( t ) ;
    }

    template <bool NA, typename T>
    inline sugar::Mean_Integer<LGLSXP,NA,T> mean( const SugarVectorExpression<LGLSXP,NA,T>& t){
        return sugar::Mean_Integer<LGLSXP,NA,T>( t ) ;
    }

    
} // Rcpp
#endif

