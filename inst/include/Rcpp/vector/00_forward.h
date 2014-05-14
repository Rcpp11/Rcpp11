#ifndef Rcpp__vector__forward_h
#define Rcpp__vector__forward_h

namespace Rcpp{
    class Na_Proxy ;
    template <int RTYPE, typename... Args> struct create_type ; 
    namespace internal{
        template <typename Vec> class string_proxy ;
        template <typename Vec> class generic_proxy ;
    }
    
}


#endif
