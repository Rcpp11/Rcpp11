#ifndef Rcpp_Module_ConstructorInvoker_h
#define Rcpp_Module_ConstructorInvoker_h
 
namespace Rcpp{
    
    template <typename Class, typename... Args>
    class ConstructorInvoker {
    public:
        typedef typename std::tuple< typename traits::input_parameter<Args>::type ...> Tuple ;
        
        ConstructorInvoker( SEXP* args_ ) : args(args_){}
        
        inline Class* invoke( ){
            return invoke_dispatch( typename traits::index_sequence<Args...>::type() ) ;
        }
        
        template <int... S>
        inline Class* invoke_dispatch( traits::sequence<S...> ){
            return new Class( get<S>() ... ) ;
        }
        
        template <int i>
        typename std::tuple_element<i, Tuple>::type get(){
            return typename std::tuple_element<i, Tuple>::type( args[i] ) ;   
        }
        
        SEXP* args ;
    } ;
 
}
#endif
