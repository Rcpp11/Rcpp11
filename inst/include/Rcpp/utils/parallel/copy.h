#ifndef RCPP11_TOOLS_COPY_PARALLEL_H
#define RCPP11_TOOLS_COPY_PARALLEL_H

namespace Rcpp{
    namespace parallel{
        
        template <typename InputIterator, typename OutputIterator>
        inline void copy_impl( InputIterator begin, InputIterator end, OutputIterator target, std::input_iterator_tag ){
            std::copy( begin, end, target ) ;
        }
        
        template <typename InputIterator, typename OutputIterator>
        inline void copy_impl( InputIterator begin, InputIterator end, OutputIterator target, std::random_access_iterator_tag ){
            R_xlen_t n = std::distance(begin, end) ;
            int nthreads = RCPP11_PARALLEL_NTHREADS ;
            if( n > RCPP11_PARALLEL_MINIMUM_SIZE ){
                std::vector<std::thread> workers(nthreads-1) ;
                R_xlen_t chunk_size = n / nthreads ;
                R_xlen_t start=0; 
                for( int i=0; i<nthreads-1; i++, start+=chunk_size){
                    workers[i] = std::thread( std::copy<InputIterator, OutputIterator>, 
                        begin + start, begin + start + chunk_size, 
                        target + start) ;   
                }
                std::copy( begin + start, end, target + start ) ;
                for( int i=0; i<nthreads-1; i++) workers[i].join() ;
            } else {
                std::copy( begin, end, target ) ;    
            }
        } 
        
        template <typename InputIterator, typename OutputIterator>
        inline void copy( InputIterator begin, InputIterator end, OutputIterator target ){
            copy_impl( begin, end, target, typename std::iterator_traits<InputIterator>::iterator_category() ) ;        
        }
        
    }    
}

#endif
