#ifndef Rcpp__sugar__Lazy_h
#define Rcpp__sugar__Lazy_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T, typename EXPR>
        class Lazy {
        public:
            inline operator T() const { 
                return static_cast<const EXPR&>(*this).get() ; 
            }
        } ;
    
    }
}

#endif
