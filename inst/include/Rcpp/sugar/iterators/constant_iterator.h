#ifndef Rcpp__sugar__iterators_constant_iterator_h
#define Rcpp__sugar__iterators_constant_iterator_h

namespace Rcpp {
    namespace sugar { 
    
        template <typename T>
        class constant_iterator {
        public:
            typedef R_xlen_t difference_type ;
            typedef T value_type ;
            typedef T* pointer ;
            typedef T reference ;
            typedef std::random_access_iterator_tag iterator_category ;
            
            constant_iterator( T value_, R_xlen_t i_) : 
                value(value_), i(i_){}
            
            constant_iterator& operator++(){ i++; return *this ; }
            constant_iterator& operator--(){ i--; return *this ; }
            constant_iterator& operator+=(R_xlen_t n){ 
                i += n ; 
                return *this; 
            }
            constant_iterator& operator-=(R_xlen_t n){ 
                i -= n ; 
                return *this; 
            }
            inline T operator*() {
                return value ;
            }
            
            constant_iterator operator+(R_xlen_t n){ 
                return constant_iterator(value, i + n) ; 
            }
            constant_iterator operator-(R_xlen_t n){ 
                return constant_iterator(value, i - n) ; 
            }
            R_xlen_t operator-( const constant_iterator& other ) const {
                return i - other.i ;
            }
        
            inline bool operator==( const constant_iterator& other ){ return i == other.i ; }
            inline bool operator!=( const constant_iterator& other ){ return i != other.i ; }
            
        private:
            T value ;
            R_xlen_t i ;
        } ;
    
    }
}
#endif
