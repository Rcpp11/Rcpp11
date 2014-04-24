#ifndef Rcpp__sugar__sd_h
#define Rcpp__sugar__sd_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>                                    
class Sd : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Sd<RTYPE,NA,T> > {
public:
    typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    
    Sd( const VEC_TYPE& object_ ) : object(object_){}

    STORAGE get() const {
        return ::sqrt( var(object).get() ) ;
    }         
private:
    const VEC_TYPE& object ;
} ;

} // sugar

template <bool NA, typename T>
inline sugar::Sd<REALSXP,NA,T> sd( const SugarVectorExpression<REALSXP,NA,T>& t){
    return sugar::Sd<REALSXP,NA,T>( t ) ;
}


} // Rcpp
#endif

