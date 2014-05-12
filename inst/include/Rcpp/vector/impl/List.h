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
        public NameProxyPolicy<VEC>
    {
        RCPP_API_IMPL(Vector)
        
        inline void set(SEXP x){
            data = r_cast<VECSXP>( x ) ;    
        }
        
        typedef SEXP value_type  ;
        typedef SEXP stored_type ;
        typedef internal::generic_proxy<VECSXP>      Proxy     ;
        typedef internal::Proxy_Iterator<Proxy>      iterator  ; 
        
        using VectorOffset<Vector>::size ;
        
        Vector( int n ) {
            reset(n);
        }
        Vector() {
            reset(0) ;
        }
    
        template <typename U>
        Vector( int n, const U& obj ) {
            reset(n) ;
            std::fill( begin(), end(), wrap(obj) ) ;
        }
        
        template <bool NA, typename Expr>
        Vector( const SugarVectorExpression<VECSXP,NA,Expr>& other ) {
            import_expression( other, typename std::is_base_of< VectorOf<VECSXP>, Expr>::type() ) ;
        }
        
        template <bool NA, typename Expr>
        Vector& operator=( const SugarVectorExpression<VECSXP, NA, Expr>& other ){
            assign_expression( other, typename std::is_base_of< VectorOf<VECSXP>, Expr>::type() ) ;
            return *this ;
        }
        
    private:
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<VECSXP,NA,Expr>& other,  std::true_type ){
            data = other.get_ref() ;    
        }
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<VECSXP,NA,Expr>& other, std::false_type ){
            reset(other.size());
            other.apply(*this) ;
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<VECSXP,NA,Expr>& other,  std::true_type ){
            data = other.get_ref() ;    
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<VECSXP,NA,Expr>& other, std::false_type ){
            int n = other.size() ;
            if( n != size() ){
                reset(n) ;    
            }
            other.apply(*this) ;
        }
        
        inline void reset(int n){
            data = Rf_allocVector(VECSXP, n) ;        
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
            return Proxy(*this, i ) ;
        }
        inline const Proxy operator[](int i) const { 
            return Proxy(const_cast<Vector&>(*this), size() ) ; 
        }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<VECSXP, Args...>::type( args... ) ;    
        }
    
        using NameProxyPolicy<VEC>::operator[] ; 
        
    } ;
    
    #undef VEC  
}
#endif
