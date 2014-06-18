#ifndef Rcpp__sugar__seq_along_h
#define Rcpp__sugar__seq_along_h

namespace Rcpp{
    namespace sugar{
    
        class SeqLen : 
            public SugarVectorExpression<int,SeqLen>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef SugarIterator<int, SeqLen> const_iterator ;
            
            SeqLen( R_xlen_t len_ ) : len(len_){}
        
            inline int operator[]( R_xlen_t i ) const {
                return 1 + i ;
            }
            inline R_xlen_t size() const { return len ; }
             
            template <typename Target>
            inline void apply( Target& target ) const {
                std::iota( target.begin(), target.end(), 1 ) ;     
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target, int nthreads ) const {
                parallel::iota(nthreads, target.begin(), target.end(), 1 ) ;    
            }
            
            inline const_iterator begin() const { return const_iterator( *this, 0 ) ; }
            inline const_iterator end() const { return const_iterator( *this, size() ) ; }
            
        private:
            R_xlen_t len ;
        } ;
        
        class Seq : 
            public SugarVectorExpression<int,Seq>, 
            public custom_sugar_vector_expression {
        public:
            typedef int value_type ;
            typedef SugarIterator<int, Seq> const_iterator ;
            
            Seq( R_xlen_t start_, R_xlen_t end_ ) : index_start(start_), index_end(end_) {}
        
            inline int operator[]( R_xlen_t i ) const {
                return index_start + i ;
            }
            inline R_xlen_t size() const { return index_end-index_start+1 ; }
             
            template <typename Target>
            inline void apply( Target& target ) const {
                std::iota( target.begin(), target.end(), index_start ) ;     
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target, int nthreads ) const {
                parallel::iota(nthreads, target.begin(), target.end(), index_start ) ;    
            }
        
            inline const_iterator begin() const { return const_iterator( *this, 0 ) ; }
            inline const_iterator end() const { return const_iterator( *this, size() ) ; }
            
        private:
            R_xlen_t index_start, index_end ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::SeqLen seq_along( const SugarVectorExpression<eT, Expr>& t){
        return sugar::SeqLen( t.size() ) ;
    }
    
    inline sugar::SeqLen seq_len( R_xlen_t n){
        return sugar::SeqLen( n ) ;
    }
    
    inline sugar::Seq seq(R_xlen_t start, R_xlen_t end){
        return sugar::Seq( start, end ) ;
    }


} // Rcpp
#endif

