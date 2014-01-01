// Copyright (C) 2014 Romain Francois

#ifndef Rcpp_api_meat_Binding_h
#define Rcpp_api_meat_Binding_h

namespace Rcpp{

    template <typename EnvironmentClass>
    template <typename T>
    typename BindingPolicy<EnvironmentClass>::Binding& BindingPolicy<EnvironmentClass>::Binding::operator=( const T& rhs){
        set( wrap(rhs) );
        return *this ;
    }
    
    template <typename EnvironmentClass>
    template <typename T>
    BindingPolicy<EnvironmentClass>::Binding::operator T() const {
        return as<T>( get() ) ;    
    }

    template <typename EnvironmentClass>
    template <typename T>
    BindingPolicy<EnvironmentClass>::const_Binding::operator T() const {
        return as<T>( get() ) ;    
    }

}

#endif
