#ifndef Rcpp__traits_or_h
#define Rcpp__traits_or_h

namespace Rcpp{
namespace traits{
	
    template <typename LHS, typename RHS>
    struct or_ {
        typedef typename std::integral_constant<bool, 
            LHS::value || RHS::value
        > type ;
    } ;
    
}
}

#endif
