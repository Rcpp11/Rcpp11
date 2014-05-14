#ifndef Rcpp__vector__impl_SimpleVector_h
#define Rcpp__vector__impl_SimpleVector_h

namespace Rcpp{
       
    #undef VEC
    #define VEC Vector<RTYPE,Storage>
    
    template <int RTYPE, typename Storage>
    class Vector :
        public VectorOf<RTYPE>,
        public SugarVectorExpression< RTYPE, true, VEC >,
        public SlotProxyPolicy<VEC>,
        public AttributeProxyPolicy<VEC>,
        public NamesProxyPolicy<VEC>,
        public AttributesProxyPolicy<VEC>, 
        public RObjectMethods<VEC>, 
        public VectorOffset<VEC>, 
        public NameProxyPolicy<VEC>, 
        private CommonVectorMethods<RTYPE,VEC>
    {
    public:
        typedef typename traits::storage_type<RTYPE>::type value_type ;
        typedef value_type stored_type  ;
        typedef typename std::conditional<RTYPE==LGLSXP,bool,stored_type>::type init_type ;
        typedef stored_type&       reference       ;
        typedef const stored_type& const_reference ;
        typedef reference          Proxy           ;
        typedef const_reference    const_Proxy     ;
        typedef value_type*        iterator        ; 
        typedef const value_type*  const_iterator  ;
        
        RCPP_VECTOR_API(RTYPE)
        
        Vector( int n, init_type x ) {
            reset(n);
            std::fill( begin(), end(), x) ;
        }
        
        Vector( std::initializer_list<init_type> list ){
            reset(list.size());
            std::copy( list.begin(), list.end(), begin() ) ;
        }
    
        inline iterator begin() { return dataptr() ; }
        inline iterator end() { return dataptr() + size() ; }
        
        inline const_iterator begin() const{ return dataptr() ; }
        inline const_iterator end() const{ return dataptr() + size() ; }
        
        inline reference operator[](int i){ 
            RCPP_CHECK_BOUNDS(i)
            return *( dataptr() + i ) ;
        }
        inline const_reference operator[](int i) const { 
            RCPP_CHECK_BOUNDS(i)
            return *( dataptr() + i ); 
        }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<RTYPE, Args...>::type( args... ) ;    
        }
        
    } ;

    #undef VEC
    
}


#endif
