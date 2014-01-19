#ifndef Rcpp_api_meat_Promise_h
#define Rcpp_api_meat_Promise_h

namespace Rcpp{ 

    template < template <class> class StoragePolicy>
    Environment_Impl<StoragePolicy> Promise_Impl<StoragePolicy>::environment() const {
        return Environment_Impl<StoragePolicy>(PRENV(Storage::get__())) ;
    }
    
    template < template <class> class StoragePolicy>
    ExpressionVector Promise_Impl<StoragePolicy>::expression() const {
        return ExpressionVector(PRCODE(Storage::get__())) ;
    }

        
}     

#endif
