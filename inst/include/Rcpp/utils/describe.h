#ifndef RCPP11_DESCRIBE_H
#define RCPP11_DESCRIBE_H

namespace Rcpp{
    
    template <typename T>
    void describe( T&& x ){
        typedef typename std::decay<T>::type type ;
        Rprintf( "T = %s\n", DEMANGLE(type) ) ;    
    }
    
}

#endif
