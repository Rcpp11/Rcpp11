#ifndef Rcpp__sugar__range_h
#define Rcpp__sugar__range_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T>
        class Range {
        public:
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            
            Range( const T& obj_) : obj(obj_) {}
            
            operator Vector<RTYPE>(){
                min_ = max_ = obj[0] ;
                if( Rcpp::traits::is_na<RTYPE>( min_ ) ) return Vector<RTYPE>::create( min_, max_ ) ;
                
                int n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++){
                    current = obj[i] ;
                    if( Rcpp::traits::is_na<RTYPE>( current ) ) return Vector<RTYPE>::create( min_, max_ ) ;
                    if( current < min_ ) min_ = current ;
                    if( current > max_ ) max_ = current ;
                    
                }
                return Vector<RTYPE>::create( min_, max_ ) ;
            }
            
            
        private:
            const T& obj ;
            STORAGE min_, max_, current ;
        } ;
    
        // version for NA = false
        template <int RTYPE, typename T>
        class Range<RTYPE,false,T> {
        public:
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            
            Range( const T& obj_) : obj(obj_) {}
            
            operator Vector<RTYPE>(){
                min_ = max_ = obj[0] ;
                
                R_xlen_t n = obj.size() ;
                for( R_xlen_t i=1; i<n; i++){
                    current = obj[i] ;
                    if( current < min_ ) {
                        min_ = current ;
                    } else if( current > max_ ) {
                        max_ = current ;
                    }
                }
                return Vector<RTYPE>::create( min_, max_ ) ;
            }
            
            
        private:
            const T& obj ;
            STORAGE min_, max_, current ;
        } ;
             
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T>
    sugar::Range<RTYPE,NA,T> range( const SugarVectorExpression<RTYPE,NA,T>& x){
        return sugar::Range<RTYPE,NA,T>(x.get_ref()) ;
    }

} // Rcpp

#endif
