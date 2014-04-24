#ifndef Rcpp__vector__impl_SimpleVector_h
#define Rcpp__vector__impl_SimpleVector_h

namespace Rcpp{
       
    #undef VEC
    #define VEC Vector<RTYPE,StoragePolicy>
    
    template <
        int RTYPE, 
        template <class> class StoragePolicy
    >
    class Vector :
        public SugarVectorExpression< RTYPE, true, VEC >,
        public StoragePolicy<VEC>,
        public SlotProxyPolicy<VEC>,
        public AttributeProxyPolicy<VEC>,
        public NamesProxyPolicy<VEC>,
        public AttributesProxyPolicy<VEC>, 
        public RObjectMethods<VEC>, 
        public VectorOffset<VEC>
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
        
        typedef internal::simple_name_proxy<RTYPE>         NameProxy       ;
        typedef internal::simple_const_name_proxy<RTYPE>   const_NameProxy ;
        
        using VectorOffset<Vector>::size ;
        
        RCPP_GENERATE_CTOR_ASSIGN(Vector)
    
        Vector( SEXP x ) {
            Storage::set__( r_cast<RTYPE>( x ) ) ;
        }
        
        Vector(int n) {
            reset(n) ;
        }
        
        Vector(){
            reset(0);
        }
    
        Vector( int n, init_type x ) {
            reset(n);
            std::fill( begin(), end(), x) ;
        }
        
        Vector( std::initializer_list<init_type> list ){
            reset(list.size());
            std::copy( list.begin(), list.end(), begin() ) ;
        }
    
        template <bool NA, typename Expr>
        Vector( const SugarVectorExpression<RTYPE,NA,Expr>& other ) {
            reset(other.size()) ;
            other.apply(*this) ;
        }
        
        template <bool NA, typename Expr>
        Vector& operator=( const SugarVectorExpression<RTYPE, NA, Expr>& expr ){
            int n = expr.size() ;
            if( n != size() ){
                reset(n) ;    
            }
            expr.apply(*this) ;
            return *this ;
        }
        
    private:
        
        inline void reset(int n){
            Storage::set__(Rf_allocVector(RTYPE, n) ) ;        
        }
        
        inline stored_type* data(){
            return reinterpret_cast<stored_type*>( DATAPTR(Storage::get__()) );    
        }
        inline const stored_type* data() const{
            return reinterpret_cast<const stored_type*>( DATAPTR(Storage::get__()) );    
        }
        
    public:
        inline iterator begin() { return data() ; }
        inline iterator end() { return data() + size() ; }
        
        inline const_iterator begin() const{ return data() ; }
        inline const_iterator end() const{ return data() + size() ; }
        
        inline Proxy operator[](int i){ return *( data() + i ) ;}
        inline const_Proxy operator[](int i) const { return *( data() + i ); }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<RTYPE, Args...>::type( args... ) ;    
        }
    
        inline NameProxy operator[]( const std::string& name ){
            return NameProxy( *this, name ) ;
        }
        inline const_NameProxy operator[]( const std::string& name ) const {
            return const_NameProxy( *this, name ) ;
        }
    } ;

    #undef VEC
    
}


#endif
