#ifndef Rcpp__sugar__mean_h
#define Rcpp__sugar__mean_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Mean : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Mean<RTYPE,NA,T> > {
public:
    typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    
    Mean( const VEC_TYPE& object_ ) : object(object_){}

    STORAGE get() const {
        return sum(object).get() / object.size() ;
    }         
private:
    const VEC_TYPE& object ;
} ;

} // sugar

template <bool NA, typename T>
inline sugar::Mean<REALSXP,NA,T> mean( const VectorBase<REALSXP,NA,T>& t){
    return sugar::Mean<REALSXP,NA,T>( t ) ;
}


} // Rcpp
#endif

