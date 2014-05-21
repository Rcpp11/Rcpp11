#ifndef Rcpp__sugar__mapply_h
#define Rcpp__sugar__mapply_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T, bool>
        struct mapply_input_type ;
        
        template <typename T>
        struct mapply_input_type<T,true> {
            typedef T type ;
        } ;
        template <typename T>
        struct mapply_input_type<T,false> {
            typedef typename std::remove_reference<T>::type::stored_type type ;
        } ;
        
        
        template <
            typename Function,
            typename... Args
        >
        class Mapply : public SugarVectorExpression< 
            Rcpp::traits::r_sexptype_traits<
                typename std::result_of<Function(typename mapply_input_type<Args, Rcpp::traits::is_primitive<Args>::type::value >::type ...)>::type
            >::rtype , 
            true ,
            Mapply<Function,Args...>
        > {
        public:                              
            typedef std::tuple<Args...> Tuple ;
            typedef std::tuple< typename mapply_input_type<Args, Rcpp::traits::is_primitive<Args>::type::value >::type ... > ETuple ;
            
            typedef typename std::result_of<Function(typename mapply_input_type<Args, Rcpp::traits::is_primitive<Args>::type::value >::type ...)>::type result_type ;
        
            Mapply( Function fun_, Args&&... args ) : 
                data( std::forward<Args>(args)... ), 
                fun(fun_), 
                n(std::get<0>(data).size()){}
        
            inline result_type operator[]( int i ) const {
                return eval(i, typename Rcpp::traits::index_sequence<Args...>::type() );
            }
            inline int size() const { 
                return n ; 
            }
        
        private:
            
            template <int... S>
            inline result_type eval( int i, Rcpp::traits::sequence<S...> ) const {
                return fun( 
                    get_ith<S>(i, typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type  >::type() ) ... 
                );    
            }
            
            template <int INDEX>
            inline typename std::tuple_element<INDEX,ETuple>::type get_ith( int , std::true_type ) const {
                return std::get<INDEX>(data) ;
            }
            
            template <int INDEX>
            inline typename std::tuple_element<INDEX,ETuple>::type get_ith( int i, std::false_type ) const {
                return std::get<INDEX>(data)[i] ;
            }
            
            Tuple data ;
            Function fun ;
            int n ;
        } ;
    
    } // sugar
    
    template <typename Function,typename... Args>
    typename sugar::Mapply<Function,Args...>
    mapply( Function fun, Args&&... args ){   
        return sugar::Mapply<Function,Args...>( fun, std::forward<Args>(args) ... ) ;
    }

} // Rcpp

#endif
