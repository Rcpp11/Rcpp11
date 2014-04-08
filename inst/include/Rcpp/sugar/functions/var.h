#ifndef Rcpp__sugar__var_h
#define Rcpp__sugar__var_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Var : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Var<RTYPE,NA,T> > {
public:
    typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    
    Var( const VEC_TYPE& object_ ) : object(object_){}

    STORAGE get() const{
        STORAGE m = mean(object).get() ;
        Minus_Vector_Primitive<RTYPE,NA,T> mm( object, m) ;
        STORAGE ssq  = sum( pow(mm,2.0) ).get() ;
        return ssq / (object.size() - 1 ) ;    
    }

private:
    const VEC_TYPE& object ;
} ;

} // sugar

template <bool NA, typename T>
inline sugar::Var<REALSXP,NA,T> var( const VectorBase<REALSXP,NA,T>& t){
    return sugar::Var<REALSXP,NA,T>( t ) ;
}


} // Rcpp
#endif

