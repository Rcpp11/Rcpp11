#ifndef Rcpp__sugar__import_h
#define Rcpp__sugar__import_h

namespace Rcpp{
    namespace sugar{
    
        template <typename InputIterator>
        class Import : 
            public SugarVectorExpression<
                typename std::iterator_traits<InputIterator>::value_type, 
                Import<InputIterator>
            >, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename std::iterator_traits<InputIterator>::value_type eT ;
            
            Import( InputIterator begin_, InputIterator end_ ) : begin(begin_), end(end_){}
            
            inline eT operator[]( R_xlen_t i) const {
                return * (begin+i) ;  
            }
            
            inline R_xlen_t size() const {
                return std::distance(begin, end) ;    
            }
            
            template <typename Target>
            void apply( Target& target ) const {
                std::copy( begin, end, target.begin() ) ;        
            }
            
        private:
            InputIterator begin, end ;    
        } ;
        
        
    } // sugar
    
    template <typename InputIterator>
    inline sugar::Import<InputIterator> 
    import( InputIterator begin, InputIterator end ){
        return sugar::Import<InputIterator>( begin, end ) ;    
    }

} // Rcpp
#endif

