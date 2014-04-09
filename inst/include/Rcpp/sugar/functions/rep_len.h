#ifndef Rcpp__sugar__rep_len_h
#define Rcpp__sugar__rep_len_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Rep_len :
    public SugarVectorExpression< RTYPE ,NA, Rep_len<RTYPE,NA,T> >,
    public custom_sugar_vector_expression {

public:
    typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

    Rep_len( const VEC_TYPE& object_, int len_ ) :
        object(object_.get_ref()), len(len_), n(object_.size()){}

    inline STORAGE operator[]( int i ) const {
        return object[ i % n ] ;
    }
    inline int size() const { return len ; }

    template <typename Target>
    inline void apply(Target& target) const {
        return apply_impl(target, typename Rcpp::traits::is_materialized<T>::type());
    }

private:
    const T& object ;
    int len, n ;

    template <typename Target>
    inline void apply_impl(Target& target, std::true_type) const {
        auto it = target.begin();
        if (n >= len) {
            std::copy(object.begin(), object.begin() + len, it);
            return;
        }

        int timesToFullCopy = len / n;
        int leftoverElems = len % n;
        for (int i=0; i < timesToFullCopy; ++i) {
            std::copy(object.begin(), object.end(), it);
            it += n;
        }
        if (leftoverElems) {
            std::copy(object.begin(), object.begin() + leftoverElems, it);
        }
    }

    template <typename Target>
    inline void apply_impl(Target& target, std::false_type) const {
        std::fill(target.begin(), target.begin() + len, object);
    }
} ;

} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::Rep_len<RTYPE,NA,T> rep_len( const VectorBase<RTYPE,NA,T>& t, int len ){
    return sugar::Rep_len<RTYPE,NA,T>( t, len ) ;
}


} // Rcpp
#endif

