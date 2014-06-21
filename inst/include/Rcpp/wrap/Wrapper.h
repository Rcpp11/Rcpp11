#ifndef Rcpp_wrap_Wrapper_h
#define Rcpp_wrap_Wrapper_h
 
namespace Rcpp{

    struct DisabledWrapper{};
    template <typename T> struct Wrapper : DisabledWrapper{} ;
    
}

#endif
