#ifndef Rcpp_Pairlist_h
#define Rcpp_Pairlist_h

namespace Rcpp{

    RCPP_API_CLASS(Pairlist_Impl), 
        public DottedPairProxyPolicy<Pairlist_Impl<StoragePolicy>>, 
        public DottedPairImpl<Pairlist_Impl<StoragePolicy>>
    {
    public:         
        typedef typename DottedPairProxyPolicy<Pairlist_Impl<StoragePolicy>>::DottedPairProxy Proxy ;
        typedef typename DottedPairProxyPolicy<Pairlist_Impl<StoragePolicy>>::const_DottedPairProxy const_Proxy;
        
        RCPP_GENERATE_CTOR_ASSIGN(Pairlist_Impl) 
        
        Pairlist_Impl(SEXP x){
            Storage::set__( r_cast<LISTSXP>(x) ) ;    
        }
        
        template<typename... Args> 
        Pairlist_Impl( const Args&... args) : Pairlist_Impl(pairlist(args...)) {}
       
    } ;
        
}
#endif
