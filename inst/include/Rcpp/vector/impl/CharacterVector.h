#ifndef Rcpp__vector__impl_CharacterVector_h
#define Rcpp__vector__impl_CharacterVector_h

namespace Rcpp{
        
    #define VEC Vector<STRSXP,StoragePolicy>
    
    template <
        template <class> class StoragePolicy
    >
    class Vector<STRSXP,StoragePolicy> :
        public VectorBase< STRSXP, true, VEC>,
        public StoragePolicy<VEC>,
        public SlotProxyPolicy<VEC>,
        public AttributeProxyPolicy<VEC>,
        public NamesProxyPolicy<VEC>,
        public AttributesProxyPolicy<VEC>, 
        public RObjectMethods<VEC>, 
        public VectorOffset<VEC>
    {
    public:
        
        typedef  SEXP value_type ;
        typedef  SEXP stored_type ;
        typedef  const char* init_type  ;
        typedef  internal::string_proxy<STRSXP>              Proxy           ;
        typedef  internal::const_string_proxy<STRSXP>        const_Proxy     ;
        typedef  internal::Proxy_Iterator<Proxy>             iterator        ; 
        typedef  internal::const_Proxy_Iterator<const_Proxy> const_iterator  ;
        typedef  internal::string_name_proxy<STRSXP>         NameProxy       ;
        typedef  internal::string_const_name_proxy<STRSXP>   const_NameProxy ;
        
        using VectorOffset<Vector>::size ;
        
        RCPP_GENERATE_CTOR_ASSIGN(Vector)
    
        Vector( SEXP x ) {
            Storage::set__( r_cast<STRSXP>( x ) ) ;
        }
        
        Vector( int n ) {
            reset(n); 
        }
        Vector() {
            reset(0); 
        }
    
        Vector( int n, const char* s ) {
            reset(n) ;
            std::fill( begin(), end(), Rf_mkChar(s) ) ;
        }
        
        Vector( const char* st ){
            reset(1) ;
            *begin() = st ;
        }         
        Vector( const std::string& st ) {
            reset(1) ;
            *begin() = st ;
        }
        
        Vector( std::initializer_list<const char*> list ){
            reset(list.size()) ;
            std::copy( list.begin(), list.end(), begin() ) ;
        }
    
        template <bool NA, typename Expr>
        Vector( const SugarVectorExpression<STRSXP,NA,Expr>& other ) {
            reset( other.size() );
            other.apply(*this) ;
        }
    
        template <bool NA, typename Expr>
        Vector& operator=( const SugarVectorExpression<STRSXP, NA, Expr>& expr ){
            int n = expr.size() ;
            if( n != size() ){
                reset(n) ;    
            }
            expr.apply(*this) ;
            return *this ;
        }
        
    private:
        
        inline void reset(int n){
            Storage::set__(Rf_allocVector(STRSXP, n) ) ;        
        }
        
        inline stored_type* data(){
            return reinterpret_cast<stored_type*>( DATAPTR(Storage::get__()) );    
        }
        inline const stored_type* data() const{
            return reinterpret_cast<const stored_type*>( DATAPTR(Storage::get__()) );    
        }
        
    public:
        
        inline iterator begin() { 
            return iterator( Proxy(*this, 0) ); 
        }
        inline iterator end() { 
            return iterator( Proxy(*this, size() ) ); 
        }
        
        inline const_iterator begin() const{ 
            return const_iterator( const_Proxy(*this, 0) );
        }
        inline const_iterator end() const{ 
            return const_iterator( const_Proxy(*this, size()) );
        }
        
        inline Proxy operator[](int i){ 
            return Proxy(*this, i ) ;
        }
        inline const_Proxy operator[](int i) const { 
            return const_Proxy(*this, i ) ; 
        }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<STRSXP, Args...>::type( args... ) ;    
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
