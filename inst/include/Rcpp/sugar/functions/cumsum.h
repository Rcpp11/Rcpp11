#ifndef Rcpp__sugar__cumsum_h
#define Rcpp__sugar__cumsum_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool HAS_NA, typename T>
        class Cumsum : public Lazy< Rcpp::Vector<RTYPE> , Cumsum<RTYPE,HAS_NA,T> > {
        public:
            typedef typename Rcpp::VectorBase<RTYPE,HAS_NA,T> VEC_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            typedef Rcpp::Vector<RTYPE> VECTOR ;
        
            Cumsum( const VEC_TYPE& object_ ) : object(object_){}
        
            VECTOR get() const {
                int n = object.size() ;
                VECTOR result( n, NA ) ; 
                STORAGE current = object[0] ;
                if( current == NA ) 
                    return result ;
                result[0] = current ;
                for( int i=1; i<n; i++){
                    current = object[i] ;
                    if( Rcpp::traits::is_na<RTYPE>(current) ) 
                        return result ;
                    result[i] = result[i-1] + current ;
                }
                return result ;
            }         
        private:
            const VEC_TYPE& object ;
        } ;
    
    } // sugar
    
    template <bool NA, typename T>
    inline sugar::Cumsum<INTSXP,NA,T> cumsum( const VectorBase<INTSXP,NA,T>& t){
        return sugar::Cumsum<INTSXP,NA,T>( t ) ;
    }
    
    template <bool NA, typename T>
    inline sugar::Cumsum<REALSXP,NA,T> cumsum( const VectorBase<REALSXP,NA,T>& t){
        return sugar::Cumsum<REALSXP,NA,T>( t ) ;
    }


} // Rcpp
#endif

