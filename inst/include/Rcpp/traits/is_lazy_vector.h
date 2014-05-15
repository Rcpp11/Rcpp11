#ifndef Rcpp__traits__is_lazy_vector_h
#define Rcpp__traits__is_lazy_vector_h
  
namespace Rcpp {
    
    struct LazyVectorBase {} ;
                  
    namespace traits {
                           
        template <typename T>
        struct is_lazy_vector : public std::is_base_of<LazyVectorBase, T> {};
        
    }
}

#endif
