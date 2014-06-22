#ifndef Rcpp_Pairlist_h
#define Rcpp_Pairlist_h

namespace Rcpp{

    template <typename Storage>
    class Pairlist_Impl:
        public DottedPairProxyPolicy<Pairlist_Impl<Storage>>, 
        public DottedPairImpl<Pairlist_Impl<Storage>>
    {
    public:         
        typedef typename DottedPairProxyPolicy<Pairlist_Impl<Storage>>::DottedPairProxy Proxy ;
        
        RCPP_API_IMPL(Pairlist_Impl) 
        
        inline void set( SEXP x){
            data = r_cast<LISTSXP>(x) ;
        }
        
        template<typename... Args> 
        Pairlist_Impl( Args&&... args) : 
            data(pairlist(std::forward<Args>(args)...)){}
       
    } ;
        
}
#endif
