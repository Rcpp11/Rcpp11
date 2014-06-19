#ifndef Rcpp__sugar__iterators_transform_iterator_h
#define Rcpp__sugar__iterators_transform_iterator_h

namespace Rcpp {
namespace sugar { 

    template <typename value_type, typename function_type, typename source_iterator>
    class transform_iterator : public std::iterator_traits<value_type*> {
    public:
        
        transform_iterator( const function_type& fun_, source_iterator source_ ) : fun(fun_), source(source_) {}
        
        transform_iterator& operator++(){
            ++source ;
            return *this ;
        }
        
        transform_iterator operator+( int n ){
            return transform_iterator(fun, source + n ) ;       
        }
        
        transform_iterator& operator+=( int n){
            source += n ;
            return *this ;
        }
        
        value_type operator*() {
            return fun(*source) ;
        }
        
        R_xlen_t operator-( const transform_iterator& other ){
            return source - other.source ;    
        }
        
        inline bool operator==( const transform_iterator& other ){ return source == other.source ; }
        inline bool operator!=( const transform_iterator& other ){ return source != other.source ; }
        
    // private:
        const function_type& fun ;
        source_iterator source ;
    } ;
        
    
}
}
#endif
