#ifndef Rcpp__sugar__mapply_h
#define Rcpp__sugar__mapply_h

namespace Rcpp{
    namespace sugar{
    
        template <
            typename Function,
            typename... Args
        >
        class Mapply : public SugarVectorExpression< 
            Rcpp::traits::r_sexptype_traits<
                typename std::result_of<Function(typename Args::stored_type ...)>::type
            >::rtype , 
            true ,
            Mapply<Function,Args...>
        > {
        public:  
            typedef std::tuple<Args...> Tuple ;
            typedef typename std::result_of<Function(typename Args::stored_type ...)>::type result_type ;
        
            Mapply( Function fun_, Args... args ) : data(args...), fun(fun_), n(std::get<0>(data).size()){}
        
            inline result_type operator[]( int i ) const {
                return eval(i, typename Rcpp::traits::index_sequence<Args...>::type() );
            }
            inline int size() const { 
                return n ; 
            }
        
        private:
            
            template <int... S>
            inline result_type eval( int i, Rcpp::traits::sequence<S...> ) const {
                return fun( std::get<S>(data)[i] ... );    
            }
            
            Tuple data ;
            Function fun ;
            int n ;
        } ;
    
    } // sugar
    
    template <typename Function,typename... Args>
    inline typename std::enable_if<
        traits::and_< typename traits::is_vector_expression<Args>::type ... >::type::value,
        typename sugar::Mapply<Function,Args...>
    >::type
    mapply( Function fun, Args... args ){   
        return sugar::Mapply<Function,Args...>( fun, args... ) ;
    }

} // Rcpp

#endif
