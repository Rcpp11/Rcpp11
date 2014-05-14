#ifndef Rcpp__vector__impl_ExpressionVector_h
#define Rcpp__vector__impl_ExpressionVector_h

namespace Rcpp{
        
    #undef VEC
    #define VEC Vector<EXPRSXP,Storage>
    
    template <typename Storage>
    class Vector<EXPRSXP,Storage> :
        public VectorOf<EXPRSXP>,
        public SugarVectorExpression< EXPRSXP, true, VEC>,
        public SlotProxyPolicy<VEC>,
        public AttributeProxyPolicy<VEC>,
        public NamesProxyPolicy<VEC>,
        public AttributesProxyPolicy<VEC>, 
        public RObjectMethods<VEC>, 
        public NameProxyPolicy<VEC>
    {
    public:
        typedef SEXP value_type  ;
        typedef SEXP stored_type ;
        typedef internal::generic_proxy<Vector> Proxy    ;
        typedef internal::Proxy_Iterator<Proxy> iterator ; 
        
        #define RTYPE EXPRSXP
        #include <Rcpp/vector/impl/RCPP_VECTOR_API.h>
        #undef RTYPE
    
    public:
        Vector( const char* st){init_from_string(st); }
        Vector( const std::string& st) { init_from_string(st.c_str()); }
        
        #include <Rcpp/vector/impl/RCPP_VECTOR_PROXY_BASED_API.h>
        
    private:
        inline void init_from_string( const char* st ){
            ParseStatus status;
            Shield<SEXP> expr = Rf_mkString( st );
            Shield<SEXP> res  = R_ParseVector(expr, -1, &status, R_NilValue);
            if( status != PARSE_OK ){
                throw parse_error() ;
            }
            data = res ;
        }
     
    } ;
    #undef VEC  
}
#endif
