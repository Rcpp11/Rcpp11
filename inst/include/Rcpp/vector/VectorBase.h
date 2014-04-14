#ifndef Rcpp__vector__VectorBase_h
#define Rcpp__vector__VectorBase_h

namespace Rcpp{
    
/** a base class for vectors, modelled after the CRTP */
template <int RTYPE, bool na, typename VECTOR>
class VectorBase : public CRTP<VECTOR>{
public:
    using CRTP<VECTOR>::get_ref ;
    
    struct r_type : std::integral_constant<int,RTYPE>{} ;
    typedef typename traits::storage_type<RTYPE>::type stored_type ; 
    typedef typename traits::storage_type<RTYPE>::type elem_type   ;
    
    inline stored_type operator[]( int i) const {
        return get_ref()[i] ;
    }
    
    inline int size() const { 
        return get_ref().size() ;
    }
    
} ;

} // namespace Rcpp
#endif
