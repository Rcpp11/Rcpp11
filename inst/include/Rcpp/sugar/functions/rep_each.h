#ifndef Rcpp__sugar__rep_each_h
#define Rcpp__sugar__rep_each_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Rep_each :
    public SugarVectorExpression< RTYPE ,NA, Rep_each<RTYPE,NA,T> >,
    public custom_sugar_vector_expression {

public:

    typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

    Rep_each( const VEC_TYPE& object_, int times_ ) :
        object(object_.get_ref()), times(times_), n(object_.size()) {}

    inline STORAGE operator[]( R_xlen_t i ) const {
        return object[ i / times ] ;
    }
    inline R_xlen_t size() const { return n * times ; }

    template <typename Target>
    inline void apply(Target& target) const {
        return apply_impl(target, typename Rcpp::traits::is_materialized<T>::type() );
    }

private:
    const T& object ;
    R_xlen_t times;
    R_xlen_t n ;

    template <typename Target>
    inline void apply_impl(Target& target, std::true_type) const {
        auto it = target.begin();
        for (R_xlen_t i=0; i < n; ++i, it += times) {
            std::fill(it, it + times, object[i]);
        }
        it += times ;
    }

    template <typename Target>
    inline void apply_impl(Target& target, std::false_type) const {
        auto it = target.begin();
        for (R_xlen_t i=0; i < n; ++i, it += times) {
            std::fill(it, it + times, object[i]);
        }
    }
} ;

} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::Rep_each<RTYPE,NA,T> rep_each( const SugarVectorExpression<RTYPE,NA,T>& t, int times ){
    return sugar::Rep_each<RTYPE,NA,T>( t, times ) ;
}


} // Rcpp
#endif

