#ifndef RCPP_SUGAR_BLOCK_1_H
#define RCPP_SUGAR_BLOCK_1_H

namespace Rcpp{
namespace sugar{                         

template <bool NA, typename OUT, typename U1, typename T1>
class SugarBlock_1 : public Rcpp::VectorBase< Rcpp::traits::r_sexptype_traits<OUT>::rtype , NA, SugarBlock_1<NA,OUT,U1,T1> > {
public:
    typedef OUT (*FunPtr)(U1) ;
    SugarBlock_1( FunPtr ptr_, const T1 & vec_) : ptr(ptr_), vec(vec_){}
        
    inline OUT operator[]( int i) const { 
        return ptr( vec[i] ) ;
    }
    inline int size() const { return vec.size() ; }
        
private:
    FunPtr ptr ;
    const T1& vec ;
};

} // sugar
} // Rcpp

#define SB1_T VectorBase<REALSXP,NA,T>
                                                            
#define SUGAR_BLOCK_1(__NAME__,__SYMBOL__)                                                \
    namespace Rcpp{                                                                       \
    template <bool NA, typename T>                                                        \
    inline sugar::SugarBlock_1<NA,double,double,SB1_T >                                   \
    __NAME__(                                                                             \
        const SB1_T& t                                                                    \
    ){                                                                                    \
        return sugar::SugarBlock_1<NA,double,double,SB1_T >(                              \
                __SYMBOL__ , t                                                            \
        ) ;                                                                               \
    }                                                                                     \
}
	
#endif
