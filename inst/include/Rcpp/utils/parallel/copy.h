#ifndef RCPP11_TOOLS_COPY_PARALLEL_H
#define RCPP11_TOOLS_COPY_PARALLEL_H

namespace Rcpp{
    namespace parallel{
        
        template <typename InputIterator, typename OutputIterator>
        inline void copy( int nthreads, InputIterator begin, InputIterator end, OutputIterator target ){ 
            R_xlen_t n = std::distance(begin, end) ;
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
        
    }    
}

#endif
