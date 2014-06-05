#ifndef Rcpp__sugar__tools_iterator_h
#define Rcpp__sugar__tools_iterator_h

namespace Rcpp {
namespace sugar { 

    /* generic sugar iterator type */
    template <typename eT, typename T>
    class SugarIterator {
    public:
        typedef eT value_type  ;
        typedef R_xlen_t difference_type  ;
        typedef value_type reference ;
        typedef const value_type const_reference ;
        typedef value_type* pointer ;
        typedef std::random_access_iterator_tag iterator_category ;
        typedef SugarIterator iterator ;
        
        SugarIterator( const T& ref_ ) : ref(ref_), index(0) {}
        SugarIterator( const T& ref_, int index_) : ref(ref_), index(index_) {}
        SugarIterator( const SugarIterator& other) : ref(other.ref), index(other.index){}
        
        inline iterator& operator++(){ index++; return *this ; }
        inline iterator operator++(int){ 
            iterator orig(*this) ;
            ++(*this); 
            return orig ;
        }
        inline iterator& operator--(){ index--; return *this ; }
        inline iterator operator--(int){ 
            iterator orig(*this) ;
            --(*this); 
            return orig ;
        }
        inline iterator operator+(difference_type n) const {
            return iterator( ref, index+n ) ;
        }
        inline iterator operator-(difference_type n) const {
            return iterator( ref, index-n ) ;
        }
        inline iterator& operator+=(difference_type n) {
            index += n ;
            return *this ;
        }
        inline iterator& operator-=(difference_type n) {
            index -= n; 
            return *this ;
        }
        inline reference operator[](R_xlen_t i){
            return ref[index+i] ;
        }
        inline const_reference operator[](R_xlen_t i) const {
            return ref[index+i] ;
        }
    
        inline reference operator*() {
            return ref[index] ;
        }
        inline const_reference operator*() const {
            return ref[index] ;
        }
        
        inline pointer operator->(){
            return &ref[index] ;
        }
    
        inline bool operator==( const iterator& y) const {
            return ( index == y.index ) ;
        }
        inline bool operator!=( const iterator& y) const {
            return ( index != y.index ) ;
        }
        inline bool operator<( const iterator& other ) const {
            return index < other.index ;
        }
        inline bool operator>( const iterator& other ) const {
            return index > other.index ;
        }
        inline bool operator<=( const iterator& other ) const {
            return index <= other.index ;        
        }
        inline bool operator>=( const iterator& other ) const {
            return index >= other.index ;
        }
                                                  
        inline difference_type operator-(const iterator& other) const {
            return index - other.index ;
        }
        
    private:   
        const T& ref ;
        R_xlen_t index ;
    } ;
    
    template <typename T>
    class constant_iterator {
    public:
        constant_iterator( T value_) : value(value_){}
        
        constant_iterator& operator++(){ return *this ; }
        inline T operator*() {
            return value ;
        }
        
        constant_iterator operator+(int n){ return *this ; }
    
    private:
        T value ;
    } ;
        
    template <typename value_type, typename function_type, typename source_iterator>
    class TransformIterator : public std::iterator_traits<value_type*> {
    public:
        
        TransformIterator( const function_type& fun_, source_iterator source_ ) : fun(fun_), source(source_) {}
        
        TransformIterator& operator++(){
            ++source ;
            return *this ;
        }
        
        TransformIterator operator+( int n ){
            return TransformIterator(fun, source + n ) ;       
        }
        
        value_type operator*() {
            return fun(*source) ;
        }
        
        R_xlen_t operator-( const TransformIterator& other ){
            return source - other.source ;    
        }
        
        inline bool operator==( const TransformIterator& other ){ return source == other.source ; }
        inline bool operator!=( const TransformIterator& other ){ return source != other.source ; }
        
    // private:
        const function_type& fun ;
        source_iterator source ;
    } ;
    
    template <typename eT, typename Expr>
    inline typename Expr::const_iterator sugar_begin(const SugarVectorExpression<eT,Expr>& obj) {
        return obj.get_ref().begin() ;
    }
    
    template <typename eT, typename Expr>
    inline typename Expr::const_iterator sugar_end(const SugarVectorExpression<eT,Expr>& obj) {
        return obj.get_ref().end() ; ;
    }
    
    
}
}
#endif
