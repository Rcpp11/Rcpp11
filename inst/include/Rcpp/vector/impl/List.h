#ifndef Rcpp__vector__impl_List_h
#define Rcpp__vector__impl_List_h

namespace Rcpp{
        
    #undef VEC
    #define VEC Vector<VECSXP,Storage>
    
    template <typename Storage>
    class Vector<VECSXP,Storage> :
        public VectorOfRTYPE<VECSXP>,
        public SugarVectorExpression<SEXP,VEC>
    {
    public:
        typedef SEXP value_type  ;
        typedef internal::generic_proxy<Vector> Proxy     ;
        typedef internal::Proxy_Iterator<Proxy> iterator  ; 
        typedef internal::Proxy_Iterator<Proxy> const_iterator ;
        
        #define RTYPE VECSXP
        #include <Rcpp/vector/impl/RCPP_VECTOR_API.h>
        #undef RTYPE
        
    public:
        
        template <typename U>
        Vector( int n, const U& obj ) {
            reset(n) ;
            std::fill( begin(), end(), wrap(obj) ) ;
        }
    
        #include <Rcpp/vector/impl/RCPP_VECTOR_PROXY_BASED_API.h>
        
    } ;
    
    #undef VEC  
}
#endif
