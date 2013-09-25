#include <Rcpp.h>
using namespace Rcpp ;
#include <tuple>

template <typename... Args> struct parameter_tuple{
    typedef typename std::tuple< 
        typename traits::input_parameter< Args >::type ...
    > type ;    
};

template <size_t i, typename... Args>
struct Feeder { 
    static void process(typename parameter_tuple<Args...>::type& target, SEXP* args){
        std::get<i>( target ).set( args[i] ) ;
        Feeder<i-1,Args...>::process(target, args);
    }
} ;
template <typename... Args>
struct Feeder<0, Args...> { 
    static void process(typename parameter_tuple<Args...>::type& target, SEXP* args ){
        std::get<0>( target ).set( args[0] ) ;
    }
} ;


template <typename... Args> class ParameterTuple {
public:
    typedef typename parameter_tuple<Args...>::type Parent ;
    
    ParameterTuple(SEXP* args_) : data(), args(args_){
        Feeder<sizeof...(Args)-1,Args...>::process( data, args) ;  
    }
    
    template <size_t i>
    typename std::tuple_element<i,Parent>::type::type get(){
        return std::get<0>(data).get() ;    
    }
    
    Parent data ;
    SEXP* args ;
} ;

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

double foo(int x, float y, double z){
    return x + y + z;
}
 
template <typename ...Args>
struct save_it_for_later {
  typename parameter_tuple<Args...>::type& params;
  double (*func)(Args...);

  double delayed_dispatch(){
    return callFunc(typename gens<sizeof...(Args)>::type());
  }

  template<int ...S>
  double callFunc(seq<S...>){
      double res = func(std::get<S>(params) ...);
      return res ;
  }
};

double fun(double x, int& y, const std::vector<double>& z){
    return x+y+z.size();
}

// [[Rcpp::export]]
double test(SEXP x, SEXP y, SEXP xx){
    gens<65> g;
    gens<65>::type s;
  
    SEXP args[3] ; args[0] = x; args[1] = y ; args[2] = xx ;
    ParameterTuple<double,int&,const std::vector<double>&> z(args) ;
    save_it_for_later<double,int&,const std::vector<double>&> saved = {z.data, fun};
    return saved.delayed_dispatch();
}

/*** R
    test(1.3, 2L, c(1,3) )
*/
