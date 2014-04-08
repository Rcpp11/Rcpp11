#ifndef Rcpp__traits_or_h
#define Rcpp__traits_or_h

namespace Rcpp{
namespace traits{

    template<typename... T>
    struct or_: std::false_type {};
    
    template <typename First, typename... Rest>
    struct or_<First,Rest...> : std::integral_constant<bool, First::value || or_<Rest...>::value>{} ;
    
}
}

#endif
