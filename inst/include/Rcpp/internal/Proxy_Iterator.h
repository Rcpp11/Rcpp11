#ifndef Rcpp__internal__Proxy_Iterator__h
#define Rcpp__internal__Proxy_Iterator__h

namespace Rcpp{
    namespace internal{
    
    template <typename PROXY>
    class Proxy_Iterator {
    public:
        typedef PROXY& reference ;
        typedef PROXY* pointer ;
        typedef int difference_type ;
        typedef PROXY value_type;
        typedef std::random_access_iterator_tag iterator_category ;
    
        Proxy_Iterator( const PROXY& proxy_ ) : proxy( proxy_ ){}
    
        inline Proxy_Iterator& operator++(){
            proxy.index++ ;
            return *this ;
        }
        inline Proxy_Iterator operator++(int){
            Proxy_Iterator orig(*this) ;
            ++(*this) ;
            return orig ;
        }
    
        inline Proxy_Iterator& operator--(){
            proxy.index-- ;
            return *this ;
        }
        inline Proxy_Iterator operator--(int){
            Proxy_Iterator orig(*this) ;
            --(*this) ;
            return orig ;
        }
    
        inline Proxy_Iterator operator+(difference_type n) const {
            return Proxy_Iterator( PROXY(*proxy.parent, proxy.index + n) ) ;
        }
        inline Proxy_Iterator operator-(difference_type n) const {
            return Proxy_Iterator( PROXY(*proxy.parent, proxy.index - n) ) ;
        }
    
        inline Proxy_Iterator& operator+=(difference_type n) {
            proxy.index += n ;
            return *this ;
        }
        inline Proxy_Iterator& operator-=(difference_type n) {
            proxy.index -= n ;
            return *this ;
        }

        inline reference operator*() {
            return proxy ;
        }
        inline pointer operator->(){
            return &proxy ;
        }
    
        inline bool operator==( const Proxy_Iterator& y) const {
            return ( this->proxy.index == y.proxy.index ) && ( this->proxy.parent == y.proxy.parent );
        }
        inline bool operator!=( const Proxy_Iterator& y) const {
            return ( this->proxy.index != y.proxy.index ) || ( this->proxy.parent != y.proxy.parent );
        }
        inline bool operator<( const Proxy_Iterator& other ) const {
            return proxy.index < other.proxy.index ;
        }
        inline bool operator>( const Proxy_Iterator& other ) const {
            return proxy.index > other.proxy.index ;
        }
        inline bool operator<=( const Proxy_Iterator& other ) const {
            return proxy.index <= other.proxy.index ;
        }
        inline bool operator>=( const Proxy_Iterator& other ) const {
            return proxy.index >= other.proxy.index ;
        }
    
        inline difference_type operator-(const Proxy_Iterator& other) const {
            return proxy.index - other.proxy.index ;
        }

        inline int index() const { return proxy.index ; }

        inline PROXY operator[](int i){ return PROXY(*proxy.parent, proxy.index + i) ; } 
    
    private:
        PROXY proxy ;
    } ;

}
}

#endif

