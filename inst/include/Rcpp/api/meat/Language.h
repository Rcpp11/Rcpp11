#ifndef Rcpp_api_meat_Language_h
#define Rcpp_api_meat_Language_h

namespace Rcpp{ 
    
    template < template <class> class StoragePolicy>
    Language_Impl<StoragePolicy>::Language_Impl( const Function& function){
          Storage::set__( Rf_lang1( function ) ) ;  
    }
         
    template < template <class> class StoragePolicy>
    void Language_Impl<StoragePolicy>::setFunction( const Function& function){
        SEXP data = Storage::get__() ;
        SETCAR( data, function );
        SET_TAG(data, R_NilValue);
    }

    
} // namespace Rcpp

#endif
