#ifndef Rcpp__sugar__iterators_replicate_iterator_h
#define Rcpp__sugar__iterators_replicate_iterator_h

namespace Rcpp {
    namespace sugar { 
    
        template <typename eT, typename function_type>
        class replicate_iterator {
        public:
            typedef R_xlen_t difference_type ;
            typedef eT value_type ;
            typedef eT* pointer ;
            typedef eT reference ;
            typedef std::random_access_iterator_tag iterator_category ;
            
            replicate_iterator( function_type fun_, R_xlen_t i_) : 
                fun(fun_), i(i_) {}
            
            replicate_iterator& operator++(){
                i++ ;
                return *this ;
            }
            
            replicate_iterator& operator+=( int n){
                i += n ;
                return *this ;
            }
            replicate_iterator& operator-=( int n){
                i -= n ;
                return *this ;
            }
            
            replicate_iterator operator+( int n ){
                return replicate_iterator(fun, i + n ) ;       
            }
            replicate_iterator operator-( int n ){
                return replicate_iterator(fun, i - n ) ;       
            }
            
            value_type operator*() {
                return fun() ;
            }
            
            R_xlen_t operator-( const replicate_iterator& other ){
                return i - other.i ;    
            }
            
            inline bool operator==( const replicate_iterator& other ){ return i == other.i ; }
            inline bool operator!=( const replicate_iterator& other ){ return i != other.i ; }
            
        private:
            function_type fun ;
            R_xlen_t i ;
        } ;
            
        
    }
}
#endif
