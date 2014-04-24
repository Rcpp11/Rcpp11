#ifndef Rcpp__sugar__seq_along_h
#define Rcpp__sugar__seq_along_h

namespace Rcpp{
    namespace sugar{
    
        class SeqLen : 
            public SugarVectorExpression< INTSXP,false,SeqLen >, 
            public custom_sugar_vector_expression {
        public:
            SeqLen( int len_ ) : len(len_){}
        
            inline int operator[]( int i ) const {
                return 1 + i ;
            }
            inline int size() const { return len ; }
             
            template <typename Target>
            inline void apply( Target& target ) const {
                std::iota( target.begin(), target.end(), 1 ) ;     
            }
        
        private:
            int len ;
        } ;
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T>
    inline sugar::SeqLen seq_along( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t){
        return sugar::SeqLen( t.size() ) ;
    }
    
    inline sugar::SeqLen seq_len( const size_t& n){
        return sugar::SeqLen( n ) ;
    }
    
    inline Range seq(int start, int end){
        return Range( start, end ) ;
    }


} // Rcpp
#endif

