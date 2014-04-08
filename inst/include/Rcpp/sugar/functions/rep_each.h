#ifndef Rcpp__sugar__rep_each_h
#define Rcpp__sugar__rep_each_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Rep_each : public SugarVectorExpression< RTYPE ,NA, Rep_each<RTYPE,NA,T> > {
public:
    typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

    Rep_each( const VEC_TYPE& object_, int times_ ) : 
        object(object_), times(times_), n(object.size()) {}

    inline STORAGE operator[]( int i ) const {
        return object[ i / times ] ;
    }
    inline int size() const { return n * times ; }

private:
    const VEC_TYPE& object ;
    int times; 
    int n ;
} ;

} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::Rep_each<RTYPE,NA,T> rep_each( const VectorBase<RTYPE,NA,T>& t, int times ){
    return sugar::Rep_each<RTYPE,NA,T>( t, times ) ;
}


} // Rcpp
#endif

