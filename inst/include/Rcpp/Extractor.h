#ifndef Rcpp__Extractor_h
#define Rcpp__Extractor_h

namespace Rcpp {
namespace traits {
        
    template <int RTYPE, bool NA, typename VECTOR>
    struct Extractor {
        typedef VECTOR type ;  
    } ;  
   
} // traits
} // Rcpp 

#endif 
