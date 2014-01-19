#ifndef Rcpp__sugar__replicate_h
#define Rcpp__sugar__replicate_h

namespace Rcpp{
namespace sugar{

    template <typename OUT, typename CallType >
    class Replicate : public Rcpp::VectorBase< Rcpp::traits::r_sexptype_traits<OUT>::rtype , true, Replicate<OUT,CallType> > {
    public:
        Replicate( size_t n_, CallType call_ ): n(n_), call(call_) {}
        
        inline OUT operator[]( int i ) const {
            return call() ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        CallType call ; 
    } ;


} // sugar

template <typename CallType>
inline sugar::Replicate<typename std::result_of<CallType()>::type, CallType> 
replicate( size_t n, CallType call){
    return sugar::Replicate<typename std::result_of<CallType()>::type, CallType>( n, call ) ;    
}



} // Rcpp
#endif

