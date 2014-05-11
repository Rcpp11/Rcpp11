#ifndef Rcpp_Pairlist_h
#define Rcpp_Pairlist_h

namespace Rcpp{

    RCPP_API_CLASS(Pairlist_Impl), 
        public DottedPairProxyPolicy<Pairlist_Impl<Storage>>, 
        public DottedPairImpl<Pairlist_Impl<Storage>>
    {
    public:         
        typedef typename DottedPairProxyPolicy<Pairlist_Impl<Storage>>::DottedPairProxy Proxy ;
        typedef typename DottedPairProxyPolicy<Pairlist_Impl<Storage>>::const_DottedPairProxy const_Proxy;
        
        RCPP_API_IMPL(Pairlist_Impl) 
        
        inline void set( SEXP x){
            data = r_cast<LISTSXP>(x) ;
        }
        
        template<typename... Args> 
        Pairlist_Impl( const Args&... args) : 
            data(pairlist(args...)){}
       
    } ;
        
}
#endif
