#ifndef Rcpp__sugar__rep_each_h
#define Rcpp__sugar__rep_each_h

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
        
        template <typename eT, typename Expr>
        class Rep_each :
            public SugarVectorExpression<eT, Rep_each<eT,Expr>>,
            public custom_sugar_vector_expression
        {
        public:
            typedef each_iterator<eT, typename Expr::const_iterator> const_iterator ;
            
            Rep_each( const SugarVectorExpression<eT,Expr>& object_, int times_ ) :
                object(object_), times(times_), n(object_.size()) {}
        
            inline R_xlen_t size() const { return n * times ; }
        
            template <typename Target>
            inline void apply(Target& target) const {
                auto it = target.begin();
                auto source_it = sugar_begin(object) ;
                for (R_xlen_t i=0; i < n; ++i, it += times, ++source_it) {
                    std::fill(it, it + times, *source_it);
                }
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target, int nthreads ) const {
                apply(target) ;    
            }
        
            inline const_iterator begin() const { 
                return const_iterator( object.get_ref().begin(), 0, times ) ; 
            }
            inline const_iterator end() const { 
                return const_iterator( object.get_ref().begin(), size(), times ) ; 
            }
            
        private:
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t times, n ;
        
        } ;
    
    }
    
    template <typename eT, typename Expr>
    inline sugar::Rep_each<eT, Expr> rep_each( const SugarVectorExpression<eT,Expr>& t, R_xlen_t times ){
        return sugar::Rep_each<eT,Expr>( t, times ) ;
    }

}
#endif

