#ifndef Rcpp__sugar__max_h
#define Rcpp__sugar__max_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool NA, typename T>
    class Max {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Max( const T& obj_) : obj(obj_) {}
        
        operator STORAGE() {
            max_ = obj[0] ;
            if( Rcpp::traits::is_na<RTYPE>( max_ ) ) return max_ ;
            
            int n = obj.size() ;
            for( int i=1; i<n; i++){
                current = obj[i] ;
                if( Rcpp::traits::is_na<RTYPE>( current ) ) return current;
                if( current > max_ ) max_ = current ;
            }
            return max_ ;
        }
        
    private:
        const T& obj ;
        STORAGE min_, max_, current ;
    } ;

    // version for NA = false
    template <int RTYPE, typename T>
    class Max<RTYPE,false,T> {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Max( const T& obj_) : obj(obj_) {}
        
        operator STORAGE() {
            max_ = obj[0] ;
            
            int n = obj.size() ;
            for( int i=1; i<n; i++){
                current = obj[i] ;
                if( current > max_ ) max_ = current ;
            }
            return max_ ;
        }
       
    private:
        const T& obj ;
        STORAGE max_, current ;
    } ;
         

} // sugar

template <int RTYPE, bool NA, typename T>
sugar::Max<RTYPE,NA,T> max( const VectorBase<RTYPE,NA,T>& x){
    return sugar::Max<RTYPE,NA,T>(x.get_ref()) ;
}

} // Rcpp

#endif
