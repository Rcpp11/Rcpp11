#ifndef Rcpp__sugar__iterators_indexing_iterator_h
#define Rcpp__sugar__iterators_indexing_iterator_h

namespace Rcpp {
    namespace sugar { 
    
        /* generic sugar iterator type */
        template <typename eT, typename T>
        class indexing_iterator {
        public:
            typedef eT value_type  ;
            typedef R_xlen_t difference_type  ;
            typedef value_type reference ;
            typedef const value_type const_reference ;
            typedef value_type* pointer ;
            typedef std::random_access_iterator_tag iterator_category ;
            typedef indexing_iterator iterator ;
            
            indexing_iterator( const T& ref_ ) : ref(ref_), index(0) {}
            indexing_iterator( const T& ref_, int index_) : ref(ref_), index(index_) {}
            indexing_iterator( const indexing_iterator& other) : ref(other.ref), index(other.index){}
            
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
    
    }
}
#endif
