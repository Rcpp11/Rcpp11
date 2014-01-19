#ifndef Rcpp_Module_FactoryInvoker_h
#define Rcpp_Module_FactoryInvoker_h
 
namespace Rcpp{
    
    template <typename Class, typename... Args>
    class FactoryInvoker {
    public:
        typedef Class* (*Fun)(Args...) ;
        typedef typename std::tuple< typename traits::input_parameter<Args>::type ...> Tuple ;
        
        FactoryInvoker( Fun factory_, SEXP* args_ ) : factory(factory_), args(args_){}
        
        inline Class* invoke( ){
            return invoke_dispatch( typename traits::index_sequence<Args...>::type() ) ;
        }
        
        template <int... S>
        inline Class* invoke_dispatch( traits::sequence<S...> ){
            return factory( get<S>() ... ) ;
        }
        
        template <int i>
        typename std::tuple_element<i, Tuple>::type get(){
            return typename std::tuple_element<i, Tuple>::type( args[i] ) ;   
        }
        
        Fun factory ;
        SEXP* args ;
    } ;

}    
#endif
