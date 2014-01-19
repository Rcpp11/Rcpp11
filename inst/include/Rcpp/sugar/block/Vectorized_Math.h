#ifndef RCPP_SUGAR_VECTORIZEDMATH_H
#define RCPP_SUGAR_VECTORIZEDMATH_H

namespace Rcpp{
namespace sugar{

extern "C" typedef double (*DDFun)(double);

template <DDFun Func, bool NA, typename VEC>
class Vectorized : public VectorBase<REALSXP, NA, Vectorized<Func,NA,VEC> >{
public:
    typedef typename Rcpp::VectorBase<REALSXP,NA,VEC> VEC_TYPE ;
    typedef typename Rcpp::traits::Extractor<REALSXP,NA,VEC>::type VEC_EXT ;
        
    Vectorized( const VEC_TYPE& object_) : object( object_.get_ref() ){}
    inline double operator[]( int i) const {
        return Func( object[i] ) ;
    }
    inline int size() const { return object.size(); }
        
private:
    const VEC_EXT& object ;     
} ;

template <DDFun Func, bool NA, typename VEC>
class Vectorized_INTSXP : public VectorBase<REALSXP, NA, Vectorized_INTSXP<Func,NA,VEC> >{
public:
    typedef typename Rcpp::VectorBase<INTSXP,NA,VEC> VEC_TYPE ;
    typedef typename Rcpp::traits::Extractor<INTSXP,NA,VEC>::type VEC_EXT ;
        
    Vectorized_INTSXP( const VEC_TYPE& object_) : object( object_.get_ref() ){}
    inline double operator[]( int i) const {
        int x = object[i] ;
        if( x == NA_INTEGER ) return NA_REAL ;
        return Func( x ) ;
    }
    inline int size() const { return object.size(); }
        
private:
    const VEC_EXT& object ;     
} ;
template <DDFun Func, typename VEC>
class Vectorized_INTSXP<Func,false,VEC> : 
    public VectorBase<REALSXP,false, Vectorized_INTSXP<Func,false,VEC> >{
public:
    typedef typename Rcpp::VectorBase<INTSXP,false,VEC> VEC_TYPE ;
    typedef typename Rcpp::traits::Extractor<INTSXP,false,VEC>::type VEC_EXT ;
        
    Vectorized_INTSXP( const VEC_TYPE& object_) : object( object_.get_ref() ){}
    inline double operator[]( int i) const {
        return Func( object[i] ) ;
    }
    inline int size() const { return object.size(); }
        
private:
    const VEC_EXT& object ;     
} ;

} // sugar
} // Rcpp

#define VECTORIZED_MATH_1(__NAME__,__SYMBOL__)                               \
namespace Rcpp{                                                              \
        template <bool NA, typename T>                                           \
        inline sugar::Vectorized<__SYMBOL__,NA,T>                                \
        __NAME__( const VectorBase<REALSXP,NA,T>& t ){                           \
                return sugar::Vectorized<__SYMBOL__,NA,T>( t ) ;                     \
        }                                                                        \
        inline sugar::Vectorized<__SYMBOL__,true,NumericVector>                  \
        __NAME__( SEXP x){ return __NAME__( NumericVector( x ) ) ; }             \
        template <bool NA, typename T>                                           \
        inline sugar::Vectorized_INTSXP<__SYMBOL__,NA,T>                         \
        __NAME__( const VectorBase<INTSXP,NA,T>& t      ){                           \
                return sugar::Vectorized_INTSXP<__SYMBOL__,NA,T>( t ) ;              \
        }                                                                        \
}


#endif
