#ifndef Rcpp__vector__impl_CharacterVector_h
#define Rcpp__vector__impl_CharacterVector_h

namespace Rcpp{
        
    #define VEC Vector<STRSXP,Storage>
    
    template <typename Storage>
    class Vector<STRSXP,Storage> :
        public VectorOf<STRSXP>,
        public SugarVectorExpression< STRSXP, true, VEC>,
        public SlotProxyPolicy<VEC>,
        public AttributeProxyPolicy<VEC>,
        public NamesProxyPolicy<VEC>,
        public AttributesProxyPolicy<VEC>, 
        public RObjectMethods<VEC>, 
        public VectorOffset<VEC>, 
        public NameProxyPolicy<VEC>, 
        private CommonVectorMethods<STRSXP,VEC>
    {
        friend class CommonVectorMethods<STRSXP,Vector> ; 
        
        using CommonVectorMethods<STRSXP,Vector>::reset ;
        using CommonVectorMethods<STRSXP,Vector>::import_expression ;
        using CommonVectorMethods<STRSXP,Vector>::import_applyable ;
        using CommonVectorMethods<STRSXP,Vector>::assign_expression ;
        using CommonVectorMethods<STRSXP,Vector>::assign_applyable ;
    
        RCPP_API_IMPL(Vector)
        
        inline void set(SEXP x){
            data =  r_cast<STRSXP>(x);   
        }
        
        typedef  SEXP value_type ;
        typedef  SEXP stored_type ;
        typedef  internal::string_proxy<Vector>  Proxy    ;
        typedef  internal::Proxy_Iterator<Proxy> iterator ; 
        
        using VectorOffset<Vector>::size ;
        
        Vector(int n) {
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
            import_expression( other, typename std::is_base_of< VectorOf<STRSXP>, Expr>::type() ) ;
        }
        
        template <bool NA, typename Expr>
        Vector& operator=( const SugarVectorExpression<STRSXP, NA, Expr>& other ){
            assign_expression( other, typename std::is_base_of< VectorOf<STRSXP>, Expr>::type() ) ;
            return *this ;
        }
        
    private:
        
        inline stored_type* dataptr(){
            return reinterpret_cast<stored_type*>( DATAPTR(data) );    
        }
        inline const stored_type* dataptr() const{
            return reinterpret_cast<const stored_type*>( DATAPTR(data) );    
        }
        
    public:
        
        inline iterator begin() { 
            return iterator( Proxy(*this, 0) ); 
        }
        inline iterator end() { 
            return iterator( Proxy(*this, size() ) ); 
        }
        
        inline const iterator begin() const{ 
            return iterator( Proxy(const_cast<Vector&>(*this), 0) );
        }
        inline iterator end() const{ 
            return iterator( Proxy(const_cast<Vector&>(*this), size()) );
        }
        
        inline Proxy operator[](int i){
            RCPP_CHECK_BOUNDS(i)
            return Proxy(*this, i ) ;
        }
        inline const Proxy operator[](int i) const {
            RCPP_CHECK_BOUNDS(i)
            return Proxy(const_cast<Vector&>(*this), i ) ; 
        }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<STRSXP, Args...>::type( args... ) ;    
        }
    
        using NameProxyPolicy<VEC>::operator[] ; 
        
    } ;
    
    
    #undef VEC
  
}
#endif
