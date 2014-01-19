#ifndef Rcpp_api_protection_h
#define Rcpp_api_protection_h

namespace Rcpp{ 

    template <typename T>
    template <typename U>
    Armor<T>::Armor( U x ) : data() {
        init( wrap(x) ) ;
    }       
        
    template <typename T>
    template <typename U>
    inline Armor<T>& Armor<T>::operator=( U x ){
        REPROTECT(data = wrap(x), index) ;
        return *this ;
    }      
    
}

#endif
