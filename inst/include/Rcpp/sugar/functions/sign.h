#ifndef Rcpp__sugar__sign_h
#define Rcpp__sugar__sign_h

namespace Rcpp{
namespace sugar{

template <bool NA, int RTYPE>
class sign__impl{
public:
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    static inline int get( STORAGE x){
        return Rcpp::traits::is_na<RTYPE>(x) ? NA_INTEGER : ( x > 0 ? 1 : (x==0 ? 0 : -1) ) ;
    }
} ;

template <int RTYPE>
class sign__impl<false,RTYPE>{
public:
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    static inline int get( STORAGE x){
        return ( x > 0 ? 1 : (x==0 ? 0 : -1) ) ;
    }
} ;


template <int RTYPE, bool NA, typename T>
class Sign : public SugarVectorExpression< INTSXP,NA, Sign<RTYPE,NA,T> > {
public:
    typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

    Sign( const VEC_TYPE& object_ ) : object(object_){}

    inline int operator[]( R_xlen_t i ) const {
        return get(i) ;
    }
    inline int size() const { return object.size() ; }

    inline int get(int i) const { return sign__impl<NA,RTYPE>::get( object[i] ); }
private:
    const VEC_TYPE& object ;
} ;

} // sugar

template <bool NA, typename T>
inline sugar::Sign<INTSXP,NA,T> sign( const SugarVectorExpression<INTSXP,NA,T>& t){
    return sugar::Sign<INTSXP,NA,T>( t ) ;
}

template <bool NA, typename T>
inline sugar::Sign<REALSXP,NA,T> sign( const SugarVectorExpression<REALSXP,NA,T>& t){
    return sugar::Sign<REALSXP,NA,T>( t ) ;
}


} // Rcpp
#endif

