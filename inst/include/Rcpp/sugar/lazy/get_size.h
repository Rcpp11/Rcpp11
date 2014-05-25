#ifndef Rcpp__sugar_lazy_get_size_h
#define Rcpp__sugar_lazy_get_size_h

namespace Rcpp{
    namespace sugar {
        
        template <typename T>
        inline R_xlen_t get_size_one( const T&, std::true_type, std::true_type ){
            return 1 ;
        }
        
        template <typename T>
        inline R_xlen_t get_size_one( const T&, std::true_type, std::false_type ){
            return 1 ;
        }
        
        template <typename T>
        inline R_xlen_t get_size_one( const T& obj, std::false_type, std::true_type ){
            return Rf_xlength(obj);
        }
        
        template <typename T>
        inline R_xlen_t get_size_one( const T& obj, std::false_type, std::false_type ){
            return obj.size();
        }
        
        template <typename T>
        inline R_xlen_t get_size_one_impl(const T& obj){
            return get_size_one( obj, 
                typename traits::is_primitive<T>::type(), 
                typename std::is_same< typename std::decay<T>::type, SEXP>::type()
            ) ;
        }
            
        template <typename Tuple, int... S>
        R_xlen_t get_size_impl( const Tuple& tuple, Rcpp::traits::sequence<S...> ){
            std::array<int, sizeof...(S)> data {{ get_size_one_impl( std::get<S>(tuple)  ) ... }} ;
            return std::accumulate( data.begin(), data.end(), 0 ) ;
        }
        
        template <typename... Args>
        R_xlen_t get_size( const std::tuple<Args...>& tuple ){
            typedef typename Rcpp::traits::index_sequence<Args...>::type Sequence ;
            return get_size_impl( tuple, Sequence() );   
        }
    }
}

#endif
