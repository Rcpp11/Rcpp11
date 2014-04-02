#ifndef Rcpp_RObject_h
#define Rcpp_RObject_h

namespace Rcpp{ 

    RCPP_API_CLASS(RObject_Impl) {
    public:
        
        RObject_Impl() {}

        RCPP_GENERATE_CTOR_ASSIGN(RObject_Impl) 
        
        RObject_Impl(SEXP x) {
            Storage::set__(x) ;    
        }

        RObject_Impl& operator=( SEXP other ){
            Storage::set__(other) ;
        }
        
   };
    
} // namespace Rcpp

#endif
