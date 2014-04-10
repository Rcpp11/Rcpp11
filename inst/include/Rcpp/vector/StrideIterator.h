#ifndef RCPP_vector_StrideIterator_h
#define RCPP_vector_StrideIterator_h

namespace Rcpp{

    template <typename iterator>
    class StrideIterator {
    public:
        using value_type = typename std::iterator_traits<iterator>::value_type ;
        using reference = typename std::iterator_traits<iterator>::reference ;
        using pointer = typename std::iterator_traits<iterator>::pointer  ;
        using difference_type = typename std::iterator_traits<iterator>::difference_type ;
        using iterator_category = typename std::iterator_traits<iterator>::iterator_category ;
        
        StrideIterator( iterator it_, int n_ ) : it(it_), n(n_){}
        
        StrideIterator& operator++(){
            it += n ;
            return *this ;
        }
        StrideIterator operator++(int){
            StrideIterator orig(it,n) ;
            it += n ;
            return orig ;
        }
        StrideIterator& operator--(){
            it -= n ;
            return *this ;
        }
        StrideIterator operator--(int){
            StrideIterator orig(it,n) ;
            it -= n ;
            return orig ;
        }
        StrideIterator operator+( int m ) const {
            return StrideIterator( it + m*n, n );    
        }
        StrideIterator operator-( int m ) const {
            return StrideIterator( it - m*n, n );    
        }
        StrideIterator& operator+=( int m ){
            it += n*m ;
            return *this ;
        }
        StrideIterator& operator-=( int m ){
            it -= n*m ;
            return *this ;
        }
        int operator-( const StrideIterator& other){
            return (other.it - it) / n ;
        }
        
        bool operator==( const StrideIterator& other)  { return it == other.it ; } 
        bool operator!=( const StrideIterator& other)  { return it != other.it ; }
        bool operator<( const StrideIterator& other )  { return it <  other.it ; }
        bool operator>( const StrideIterator& other )  { return it >  other.it ; }
        bool operator<=( const StrideIterator& other ) { return it <= other.it ; }
        bool operator>=( const StrideIterator& other ) { return it >= other.it ; }
        
        inline reference operator[](int i){
            return it[i*n] ;    
        }
        inline reference operator*() {
            return *it ;
        }
        
    private:
        iterator it ;
        int n ;
    } ;
    
}

#endif    
