#ifndef RCPP11_Strict_H
#define RCPP11_Strict_H

namespace Rcpp {

    template <typename Class>
    class Strict {
    public:
        Strict( SEXP x ) : obj(x){
            if( !is<Class>(x) ){
                stop( "not compatible with class %s", DEMANGLE(Class) ) ;    
            }
        }
        
        inline Class get() const {
            return Class(obj) ;    
        }
        
    private:
        SEXP obj ;
    } ;
    
}

#endif

