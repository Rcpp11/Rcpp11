#ifndef Rcpp_api_meat_NamesProxy_h
#define Rcpp_api_meat_NamesProxy_h

namespace Rcpp{
                              
    template <typename CLASS>
    NamesProxy<CLASS>& NamesProxy<CLASS>::operator=( std::initializer_list<const char*> x ){
        *this = CharacterVector(x) ;
        return *this ;        
    }
}

#endif
