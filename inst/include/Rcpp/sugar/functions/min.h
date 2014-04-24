#ifndef Rcpp__sugar__min_h
#define Rcpp__sugar__min_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool NA, typename T>
    class Min {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Min( const T& obj_) : obj(obj_) {}
        
        operator STORAGE() {
            min_ = obj[0] ;
            if( Rcpp::traits::is_na<RTYPE>( min_ ) ) return min_ ;
            
            int n = obj.size() ;
            for( int i=1; i<n; i++){
                current = obj[i] ;
                if( Rcpp::traits::is_na<RTYPE>( current ) ) return current;
                if( current < min_ ) min_ = current ;
            }
            return min_ ;
        }
    
        const T& obj ;
        STORAGE min_, max_, current ;
    } ;

    // version for NA = false
    template <int RTYPE, typename T>
    class Min<RTYPE,false,T> {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Min( const T& obj_) : obj(obj_) {}
        
        operator STORAGE() {
            min_ = obj[0] ;
            
            int n = obj.size() ;
            for( int i=1; i<n; i++){
                current = obj[i] ;
                if( current < min_ ) min_ = current ;
            }
            return min_ ;
        }
    
        const T& obj ;
        STORAGE min_, current ;
    } ;

    
} // sugar


template <int RTYPE, bool NA, typename T>
sugar::Min<RTYPE,NA,T> min( const SugarVectorExpression<RTYPE,NA,T>& x){
    return sugar::Min<RTYPE,NA,T>(x.get_ref()) ;
}

} // Rcpp

#endif
