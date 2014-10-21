#ifndef RCPP11_TOOLS_generate_PARALLEL_H
#define RCPP11_TOOLS_generate_PARALLEL_H

namespace Rcpp{
    namespace parallel{
        
        template <typename OutputIterator, typename Size, typename Generator>
        inline void generate_n( OutputIterator begin, Size n, Generator gen ){ 
            int nthreads = RCPP11_PARALLEL_NTHREADS ;
            if( n > RCPP11_PARALLEL_MINIMUM_SIZE ){
                std::vector<std::thread> workers(nthreads-1) ;
                Size chunk_size = n / nthreads ;
                Size pos = 0;
                for( int i=0; i<nthreads-1; i++, pos += chunk_size){
                    workers[i] = std::thread( std::generate_n<OutputIterator, R_xlen_t, Generator>, 
                        begin + pos, chunk_size, gen) ;   
                }
                std::generate_n( begin + pos, n-pos, gen ) ;
                for( int i=0; i<nthreads-1; i++) workers[i].join() ;
            } else {
                std::generate_n( begin, n, gen ) ;
            }
        }
        
    }    
}

#endif
