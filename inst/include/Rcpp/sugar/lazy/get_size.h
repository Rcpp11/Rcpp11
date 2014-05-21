#ifndef Rcpp__sugar_lazy_get_size_h
#define Rcpp__sugar_lazy_get_size_h

namespace Rcpp{
    namespace sugar {
        template <typename T>
        inline int get_size_one( const T&, std::true_type, std::true_type ){
            return 1 ;
        }
        
        template <typename T>
        inline int get_size_one( const T&, std::true_type, std::false_type ){
            return 1 ;
        }
        
        template <typename T>
        inline int get_size_one( const T& obj, std::false_type, std::true_type ){
            return Rf_length(obj);
        }
        
        template <typename T>
        inline int get_size_one( const T& obj, std::false_type, std::false_type ){
            return obj.size();
        }
        
        template <typename First>
        int get_size( const First& first){
            return get_size_one<First>(first, typename traits::is_primitive<First>::type(), typename std::is_same<First, SEXP>::type() ) ;
        }
        
        template <typename First, typename... Rest>
        int get_size( const First& first, Rest... rest ){
            return get_size_one<First>(first, typename traits::is_primitive<First>::type(), typename std::is_same<First, SEXP>::type() ) + get_size(rest...) ;
        }
      
    }
}

#endif
