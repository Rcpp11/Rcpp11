#ifndef Rcpp_wrap_TupleWrapper_h
#define Rcpp_wrap_TupleWrapper_h
 
namespace Rcpp{

    template <typename... Args>
    struct tuple_wrapper_type ;
    
    template <typename... Args> 
    struct Wrapper<std::tuple<Args...>> : LazyVectorWrapper<typename tuple_wrapper_type<Args...>::type> {} ;
    
}

#endif
