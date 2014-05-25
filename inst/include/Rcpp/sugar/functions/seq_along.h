#ifndef Rcpp__sugar__seq_along_h
#define Rcpp__sugar__seq_along_h

namespace Rcpp{
    namespace sugar{
    
        class SeqLen : 
            public SugarVectorExpression< INTSXP,false,SeqLen >, 
            public custom_sugar_vector_expression {
        public:
            SeqLen( R_xlen_t len_ ) : len(len_){}
        
            inline int operator[]( R_xlen_t i ) const {
                return 1 + i ;
            }
            inline R_xlen_t size() const { return len ; }
             
            template <typename Target>
            inline void apply( Target& target ) const {
                std::iota( target.begin(), target.end(), 1 ) ;     
            }
        
        private:
            R_xlen_t len ;
        } ;
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T>
    inline sugar::SeqLen seq_along( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t){
        return sugar::SeqLen( t.size() ) ;
    }
    
    inline sugar::SeqLen seq_len( R_xlen_t n){
        return sugar::SeqLen( n ) ;
    }
    
    inline Range seq(R_xlen_t start, R_xlen_t end){
        return Range( start, end ) ;
    }


} // Rcpp
#endif

