#ifndef RCPP11_TOOLS_TRANSFORM_PARALLEL_H
#define RCPP11_TOOLS_TRANSFORM_PARALLEL_H

namespace Rcpp{
    namespace parallel{
    
        template <typename InputIterator, typename OutputIterator, typename Function>
        void transform( InputIterator begin, InputIterator end, OutputIterator target, Function fun ){ 
            int nthreads = RCPP11_PARALLEL_NTHREADS ;
            R_xlen_t n = std::distance(begin, end) ;
            if( n > RCPP11_PARALLEL_MINIMUM_SIZE ){   
                std::vector<std::thread> workers(nthreads-1) ;
                R_xlen_t chunk_size = n / nthreads ;
                R_xlen_t start=0; 
                for( int i=0; i<nthreads-1; i++, start+=chunk_size){
                    workers[i] = std::thread( std::transform<InputIterator, OutputIterator, Function>, 
                        begin + start, begin + start + chunk_size, 
                        target + start, 
                        fun) ;   
                }
                std::transform( begin + start, end, target + start, fun ) ;
                for( int i=0; i<nthreads-1; i++) workers[i].join() ;
            } else {
                std::transform( begin, end, target, fun ) ;
            }
        }
        
    }   
}

#endif
