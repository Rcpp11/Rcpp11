#ifndef Rcpp_api_meat_Reference_h
#define Rcpp_api_meat_Reference_h

namespace Rcpp{

    template <template <class> class StoragePolicy>
    template <typename T>
    Reference_Impl<StoragePolicy>::Reference_Impl(const T& object ) : Reference_Impl(wrap(object)) {}
    
}
#endif
