#ifndef RCPP11_TOOLS_COPY_PARALLEL_H
#define RCPP11_TOOLS_COPY_PARALLEL_H

namespace Rcpp{
    
    template <typename InputIterator, typename OutputIterator>
    inline void copy_parallel( int, InputIterator begin, InputIterator end, OutputIterator target ){ 
        std::copy( begin, end, target ) ;
    }
    
}

#endif
