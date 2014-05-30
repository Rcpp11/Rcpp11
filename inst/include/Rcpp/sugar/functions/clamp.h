#ifndef Rcpp__sugar__clamp_h
#define Rcpp__sugar__clamp_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA>
        struct clamp_operator{
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
            clamp_operator(STORAGE lhs_, STORAGE rhs_ ) : lhs(lhs_), rhs(rhs_){}
            
            inline STORAGE operator()(STORAGE x) const {
                return x < lhs ? lhs : (x > rhs ? rhs : x ) ;
            }
            STORAGE lhs, rhs ;    
        } ;

    } // sugar

    template <int RTYPE, bool NA, typename T>
    inline auto clamp( 
        typename Rcpp::traits::storage_type<RTYPE>::type lhs,
        const Rcpp::SugarVectorExpression<RTYPE,NA,T>& vec,  
        typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ) -> decltype( sapply( vec, sugar::clamp_operator<RTYPE,NA>(lhs, rhs) ) ) {
        return sapply( vec, sugar::clamp_operator<RTYPE,NA>(lhs, rhs) ) ;
    }


} // Rcpp

#endif
