#ifndef Rcpp__sugar__iterator_each_iterator_h
#define Rcpp__sugar__iterator_each_iterator_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename SourceIterator>
        class each_iterator {
        public:
            typedef R_xlen_t difference_type ;
            typedef eT value_type ;
            typedef eT* pointer ;
            typedef eT reference ;
            typedef std::random_access_iterator_tag iterator_category ;
        
            each_iterator(SourceIterator source_, R_xlen_t i_, R_xlen_t times_ ) :
                i(i_), times(times_), j( i % times ), source(source_ + (i / times) ){} 
            
            each_iterator& operator++(){
                i++ ;
                j++ ;
                if( j == times ){
                    ++source ;
                    j = 0 ;    
                }
                return *this ;
            }
            each_iterator& operator--(){
                i-- ; 
                j-- ;
                if( j < 0 ){
                    j = times - 1 ;
                    --source ;
                }
                return *this ;
            }
            each_iterator& operator+=(R_xlen_t n){
                i += n ;
                for( R_xlen_t k=0; k<n; k++){
                    j++ ;
                    if( j == times ){
                        j = 0 ;
                        ++source ;
                    }
                }
                return *this ;
            }
            each_iterator& operator-=(R_xlen_t n){
                i -= n ;
                for( R_xlen_t k=0; k<n; k++){
                    j-- ;
                    if( j < 0 ){
                        j = times - 1 ;
                        --source ;
                    }
                }
                return *this ;
            }
            
            inline eT operator*(){ return *source ; }
              
            inline each_iterator operator+( R_xlen_t n){
                each_iterator copy(*this) ;
                copy += n ;
                return copy;
            }
            inline each_iterator operator-( R_xlen_t n){
                each_iterator copy(*this) ;
                copy -= n ;
                return copy;
            }
            R_xlen_t operator-( const each_iterator& other ) const {
                return i - other.i ;
            }  
            
            inline bool operator==( const each_iterator& other ){ return i == other.i ; }
            inline bool operator!=( const each_iterator& other ){ return i != other.i ; }
        
        private:
            R_xlen_t i ;
            R_xlen_t times ;
            R_xlen_t j ;
            
            SourceIterator source ;
            
        } ;

    }
}
#endif
