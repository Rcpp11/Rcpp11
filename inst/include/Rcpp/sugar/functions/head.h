#ifndef Rcpp__sugar__head_h
#define Rcpp__sugar__head_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Head : 
    public SugarVectorExpression< RTYPE ,NA, Head<RTYPE,NA,T> >, 
    public custom_sugar_vector_expression 
{
public:
    typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

    Head( const VEC_TYPE& object_, R_xlen_t n_ ) : object(object_), n(n_) {
        if( n < 0 ){
            n = object.size() + n ;
        }
    }

    inline STORAGE operator[]( R_xlen_t i ) const {
        return object[ i ] ;
    }
    inline R_xlen_t size() const { return n; }

    template <typename Target>
    inline void apply( Target& target ) const {
        std::copy_n( sugar_begin(object), n, target.begin() ) ;   
    }
    
private:
    const VEC_TYPE& object ;
    R_xlen_t n ;
} ;

} // sugar

template <int RTYPE,bool NA, typename T>
inline sugar::Head<RTYPE,NA,T> head( 
    const SugarVectorExpression<RTYPE,NA,T>& t, 
    R_xlen_t n 
    ){
    return sugar::Head<RTYPE,NA,T>( t, n ) ;
}

} // Rcpp
#endif

