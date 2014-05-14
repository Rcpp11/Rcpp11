#ifndef Rcpp__vector__impl_List_h
#define Rcpp__vector__impl_List_h

namespace Rcpp{
        
    #undef VEC
    #define VEC Vector<VECSXP,Storage>
    
    template <typename Storage>
    class Vector<VECSXP,Storage> :
        public VectorOf<VECSXP>,
        public SugarVectorExpression< VECSXP, true, VEC>,
        public SlotProxyPolicy<VEC>,
        public AttributeProxyPolicy<VEC>,
        public NamesProxyPolicy<VEC>,
        public AttributesProxyPolicy<VEC>, 
        public RObjectMethods<VEC>, 
        public VectorOffset<VEC>, 
        public NameProxyPolicy<VEC>, 
        private CommonVectorMethods<VECSXP,VEC>
    {
    public:
        typedef SEXP value_type  ;
        typedef SEXP stored_type ;
        typedef internal::generic_proxy<Vector> Proxy     ;
        typedef internal::Proxy_Iterator<Proxy> iterator  ; 
        
        RCPP_VECTOR_API(VECSXP)
        
        
        template <typename U>
        Vector( int n, const U& obj ) {
            reset(n) ;
            std::fill( begin(), end(), wrap(obj) ) ;
        }
    
        inline iterator begin() { 
            return iterator( Proxy(*this, 0) ); 
        }
        inline iterator end() { 
            return iterator( Proxy(*this, size() ) ); 
        }
        
        inline const iterator begin() const{ 
            return iterator( Proxy(const_cast<Vector&>(*this), 0) );
        }
        inline const iterator end() const{ 
            return iterator( Proxy(const_cast<Vector&>(*this), size() ) );
        }
        
        inline Proxy operator[](int i){ 
            RCPP_CHECK_BOUNDS(i)
            return Proxy(*this, i ) ;
        }
        inline const Proxy operator[](int i) const { 
            RCPP_CHECK_BOUNDS(i)
            return Proxy(const_cast<Vector&>(*this), size() ) ; 
        }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<VECSXP, Args...>::type( args... ) ;    
        }
    
    } ;
    
    #undef VEC  
}
#endif
