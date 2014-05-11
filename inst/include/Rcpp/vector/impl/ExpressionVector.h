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
        public VectorOffset<VEC>
    {
        RCPP_API_IMPL(Vector)
        
        inline void set(SEXP x){
            data = r_cast<EXPRSXP>( x ) ;        
        }
        
        typedef SEXP value_type  ;
        typedef SEXP stored_type ;
        typedef internal::generic_proxy<EXPRSXP>            Proxy           ;
        typedef internal::const_generic_proxy<EXPRSXP>      const_Proxy     ;
        typedef internal::Proxy_Iterator<Proxy>             iterator        ; 
        typedef internal::const_Proxy_Iterator<const_Proxy> const_iterator  ;
        typedef internal::generic_name_proxy<EXPRSXP>       NameProxy       ;
        typedef internal::generic_const_name_proxy<EXPRSXP> const_NameProxy ;
        
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
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<EXPRSXP,NA,Expr>& other,  std::true_type ){
            data = other.get_ref() ;   
        }
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<EXPRSXP,NA,Expr>& other, std::false_type ){
            reset(other.size());
            other.apply(*this) ;
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<EXPRSXP,NA,Expr>& other,  std::true_type ){
            data = other.get_ref() ;    
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<EXPRSXP,NA,Expr>& other, std::false_type ){
            int n = other.size() ;
            if( n != size() ){
                reset(n) ;    
            }
            other.apply(*this) ;
        }
        
        inline void init_from_string( const char* st ){
            ParseStatus status;
            Shield<SEXP> expr = Rf_mkString( st );
            Shield<SEXP> res  = R_ParseVector(expr, -1, &status, R_NilValue);
            if( status != PARSE_OK ){
                throw parse_error() ;
            }
            data = res ;
        }
        
        inline void reset(int n){
            data = Rf_allocVector(EXPRSXP, n) ;        
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
        
        inline const_iterator begin() const{ 
            return const_iterator( const_Proxy(*this, 0) );
        }
        inline const_iterator end() const{ 
            return const_iterator( const_Proxy(*this, size() ) );
        }
        
        inline Proxy operator[](int i){ 
            return Proxy(*this, i ) ;
        }
        inline const_Proxy operator[](int i) const { 
            return const_Proxy(*this, size() ) ; 
        }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<EXPRSXP, Args...>::type( args... ) ;    
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
