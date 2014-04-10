#ifndef Rcpp__vector__forward_h
#define Rcpp__vector__forward_h

namespace Rcpp{
    class Na_Proxy ;
    
    namespace internal{
        template <int RTYPE> class string_proxy ;
        template <int RTYPE> class const_string_proxy ;
        template <int RTYPE> class generic_proxy ;
        template <int RTYPE> class const_generic_proxy ;
        template <int RTYPE> class simple_name_proxy ; 
        template <int RTYPE> class string_name_proxy ;
        template <int RTYPE> class generic_name_proxy ;
    }
    
}


#endif
