#ifndef Rcpp__sugar__import_h
#define Rcpp__sugar__import_h

namespace Rcpp{
    namespace sugar{
    
        template <typename InputIterator>
        class Import : 
            public SugarVectorExpression<
                typename std::iterator_traits<InputIterator>::value_type, 
                Import<InputIterator>
            >
        {
        public:
            typedef InputIterator const_iterator ;
            
            Import( InputIterator src_begin_, InputIterator src_end_ ) : src_begin(src_begin_), src_end(src_end_){}
            
            inline R_xlen_t size() const {
                return std::distance(src_begin, src_end) ;    
            }
            
            inline const_iterator begin() const { return src_begin ; }
            inline const_iterator end() const { return src_end ; }
            
        private:
            InputIterator src_begin, src_end ;    
        } ;
        
        
    } // sugar
    
    template <typename InputIterator>
    inline sugar::Import<InputIterator> 
    import( InputIterator begin, InputIterator end ){
        return sugar::Import<InputIterator>( begin, end ) ;    
    }

} // Rcpp
#endif

