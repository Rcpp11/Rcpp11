// Copyright (C) 2013 - 2014 Romain Francois

#ifndef Rcpp__traits__all__h
#define Rcpp__traits__all__h

namespace Rcpp{
    namespace traits{
        
        template<typename... T>
        struct and_: std::true_type {};
        
        template<typename First, typename... Rest>
        struct and_<First, Rest...> : std::integral_constant<bool, First::value && and_<Rest...>::value> {};

    }
}

#endif

