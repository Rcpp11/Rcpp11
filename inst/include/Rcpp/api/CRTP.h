#ifndef Rcpp_api_CRTP_h
#define Rcpp_api_CRTP_h

namespace Rcpp{

    template <typename T>
    struct CRTP{
        inline T& get_ref(){ return static_cast<T&>(*this) ;}
        inline const T& get_ref() const { return static_cast<const T&>(*this) ;}
    } ;
        
}

#endif
