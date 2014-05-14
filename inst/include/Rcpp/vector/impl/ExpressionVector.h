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
        public VectorOffset<VEC>, 
        public NameProxyPolicy<VEC>, 
        private CommonVectorMethods<EXPRSXP,VEC>
    {
        friend class CommonVectorMethods<EXPRSXP,Vector> ; 
        
        using CommonVectorMethods<EXPRSXP,Vector>::reset ;
        using CommonVectorMethods<EXPRSXP,Vector>::import_expression ;
        using CommonVectorMethods<EXPRSXP,Vector>::import_applyable ;
        using CommonVectorMethods<EXPRSXP,Vector>::assign_expression ;
        using CommonVectorMethods<EXPRSXP,Vector>::assign_applyable ;
        
        RCPP_API_IMPL(Vector)
        
        inline void set(SEXP x){
            data = r_cast<EXPRSXP>( x ) ;        
        }
        
        typedef SEXP value_type  ;
        typedef SEXP stored_type ;
        typedef internal::generic_proxy<Vector> Proxy    ;
        typedef internal::Proxy_Iterator<Proxy> iterator ; 
        
        using VectorOffset<Vector>::size ;
        
        Vector( int n ) {
            reset(n) ;
        }
        Vector() {
            reset(0) ;
        }
    
        Vector( const char* st){init_from_string(st); }
        Vector( const std::string& st) { init_from_string(st.c_str()); }
        
        template <bool NA, typename Expr>
        Vector( const SugarVectorExpression<EXPRSXP,NA,Expr>& other ) {
            import_expression( other, typename std::is_base_of< VectorOf<EXPRSXP>, Expr>::type() ) ;
        }
        
        template <bool NA, typename Expr>
        Vector& operator=( const SugarVectorExpression<EXPRSXP, NA, Expr>& other ){
            assign_expression( other, typename std::is_base_of< VectorOf<EXPRSXP>, Expr>::type() ) ;
            return *this ;
        }
        
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
            return typename create_type<EXPRSXP, Args...>::type( args... ) ;    
        }
    
        using NameProxyPolicy<VEC>::operator[] ;
        
    } ;
    #undef VEC  
}
#endif
