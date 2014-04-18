#ifndef Rcpp__sugar__mean_h
#define Rcpp__sugar__mean_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T> class Mean ;
        
        // REALSXP
        template <bool NA, typename T> 
        class Mean<REALSXP,NA,T> : Lazy<double, Mean<REALSXP,NA,T> >{
        public:
            typedef VectorBase<REALSXP,NA,T> VEC_TYPE ;
            
            Mean( const VEC_TYPE& object_ ) : object(object_){}
            
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
        class Mean<CPLXSXP,NA,T> : public Lazy< Rcomplex, Mean<CPLXSXP,NA,T> >{
        public:
            typedef VectorBase<CPLXSXP,NA,T> VEC_TYPE ;
            
            Mean( const VEC_TYPE& object_ ) : object(object_){}
            
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
        
    } // sugar
    
    template <bool NA, typename T>
    inline sugar::Mean<REALSXP,NA,T> mean( const VectorBase<REALSXP,NA,T>& t){
        return sugar::Mean<REALSXP,NA,T>( t ) ;
    }

    template <bool NA, typename T>
    inline sugar::Mean<CPLXSXP,NA,T> mean( const VectorBase<CPLXSXP,NA,T>& t){
        return sugar::Mean<CPLXSXP,NA,T>( t ) ;
    }

} // Rcpp
#endif

