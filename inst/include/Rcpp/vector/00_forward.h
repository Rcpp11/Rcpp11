#ifndef Rcpp__vector__foward_h
#define Rcpp__vector__foward_h

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
    
    namespace traits {
        template <int RTYPE, bool NA, typename VECTOR> struct Extractor ;
        
        template <int RTYPE> struct r_vector_cache_type ;
        template <int RTYPE> class r_vector_cache ;
        
        template <int RTYPE> struct r_vector_name_proxy ;
        template <int RTYPE> struct r_vector_const_name_proxy ;
        template <int RTYPE> struct r_vector_proxy ;
        template <int RTYPE> struct r_vector_const_proxy ;
        
        template <int RTYPE> struct r_vector_iterator ;
        template <int RTYPE> struct r_vector_const_iterator ;
    }

}


#endif
