#ifndef Rcpp__vector__eval_methods_h
#define Rcpp__vector__eval_methods_h

namespace Rcpp{
namespace internal{

    template <int RTYPE, template <class> class StoragePolicy> 
    class eval_methods {} ;
    
    template <template <class> class StoragePolicy> 
    class eval_methods<EXPRSXP, StoragePolicy> {
    public:
        SEXP eval() ;
        SEXP eval(SEXP) ;
    } ;
      
}
}
#endif
