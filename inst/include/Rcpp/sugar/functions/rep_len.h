#ifndef Rcpp__sugar__rep_len_h
#define Rcpp__sugar__rep_len_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Rep_len :
    public SugarVectorExpression< RTYPE ,NA, Rep_len<RTYPE,NA,T> >,
    public custom_sugar_vector_expression {

public:
    typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

    Rep_len( const VEC_TYPE& object_, int len_ ) :
        object(object_.get_ref()), len(len_), n(object_.size()){}

    inline STORAGE operator[]( R_xlen_t i ) const {
        return object[ i % n ] ;
    }
    inline R_xlen_t size() const { return len ; }

    template <typename Target>
    inline void apply(Target& target) const {
        if (n >= len) {
            std::copy_n(sugar_begin(*this), len, target.begin() );
            return;
        }

        int timesToFullCopy = len / n;
        int leftoverElems = len % n;
        
        // first copy data from the sugar expression
        auto it = target.begin();
        std::copy_n(sugar_begin(*this), n, it);
        it += n;
                
        // then copy the materialized part into the rest of the output
        for (R_xlen_t i=1; i < timesToFullCopy; ++i) {
            std::copy_n(target.begin(), n, it);
            it += n;
            
        }
        if (leftoverElems) {
            std::copy_n(target.begin(), leftoverElems, it);
        }
        
    }

private:
    const T& object ;
    int len, n ;

} ;

} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::Rep_len<RTYPE,NA,T> rep_len( const SugarVectorExpression<RTYPE,NA,T>& t, int len ){
    return sugar::Rep_len<RTYPE,NA,T>( t, len ) ;
}


} // Rcpp
#endif

