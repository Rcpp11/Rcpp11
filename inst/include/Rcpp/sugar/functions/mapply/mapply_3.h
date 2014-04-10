#ifndef Rcpp__sugar__mapply_3_h
#define Rcpp__sugar__mapply_3_h

namespace Rcpp{
namespace sugar{

template <
    int RTYPE_1, bool NA_1, typename T_1, 
    int RTYPE_2, bool NA_2, typename T_2, 
    int RTYPE_3, bool NA_3, typename T_3, 
    typename Function
>
class Mapply_3 : public SugarVectorExpression< 
    Rcpp::traits::r_sexptype_traits<
        typename std::result_of<Function>::type
    >::rtype , 
    true ,
    Mapply_3<RTYPE_1,NA_1,T_1,RTYPE_2,NA_2,T_2,RTYPE_3,NA_3,T_3,Function>
> {
public:         
    typedef typename std::result_of<Function>::type result_type ;

    typedef Rcpp::VectorBase<RTYPE_1,NA_1,T_1> VEC_1 ;
    typedef Rcpp::VectorBase<RTYPE_2,NA_2,T_2> VEC_2 ;
    typedef Rcpp::VectorBase<RTYPE_3,NA_3,T_3> VEC_3 ;

    Mapply_3( const VEC_1& vec_1_, const VEC_2& vec_2_, const VEC_3& vec_3_, Function fun_ ) : 
        vec_1(vec_1_), vec_2(vec_2_), vec_3(vec_3_), fun(fun_){}

    inline result_type operator[]( int i ) const {
        return fun( vec_1[i], vec_2[i], vec_3[i] );
    }
    inline int size() const { return vec_1.size() ; }

private:
    const VEC_1& vec_1 ;
    const VEC_2& vec_2 ;
    const VEC_3& vec_3 ;
    Function fun ;
} ;

} // sugar

template <
    int RTYPE_1, bool NA_1, typename T_1, 
    int RTYPE_2, bool NA_2, typename T_2, 
    int RTYPE_3, bool NA_3, typename T_3, 
    typename Function
    >
inline sugar::Mapply_3<RTYPE_1,NA_1,T_1,RTYPE_2,NA_2,T_2,RTYPE_3, NA_3,T_3,Function> 
mapply( 
    const Rcpp::VectorBase<RTYPE_1,NA_1,T_1>& t1, 
    const Rcpp::VectorBase<RTYPE_2,NA_2,T_2>& t2, 
    const Rcpp::VectorBase<RTYPE_3,NA_3,T_3>& t3, 
    Function fun
){
    return sugar::Mapply_3<RTYPE_1,NA_1,T_1,RTYPE_2,NA_2,T_2,RTYPE_3,NA_3,T_3,Function>( t1, t2, t3, fun ) ;
}

} // Rcpp

#endif
