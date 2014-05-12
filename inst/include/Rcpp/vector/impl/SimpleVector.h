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
        public VectorOffset<VEC>
    {
        RCPP_API_IMPL(Vector)
        
        inline void set(SEXP x){
            data =  r_cast<RTYPE>(x);   
        }
        
        typedef typename traits::storage_type<RTYPE>::type value_type ;
        typedef value_type stored_type  ;
        typedef typename std::conditional<RTYPE==LGLSXP,bool,stored_type>::type init_type ;
        typedef stored_type&       reference       ;
        typedef const stored_type& const_reference ;
        typedef reference          Proxy           ;
        typedef const_reference    const_Proxy     ;
        typedef value_type*        iterator        ; 
        typedef const value_type*  const_iterator  ;
        
        typedef internal::simple_name_proxy<RTYPE>         NameProxy  ;
        
        using VectorOffset<Vector>::size ;
        
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
            import_expression( other, typename std::is_base_of< VectorOf<RTYPE>, Expr>::type() ) ;
        }
        
        template <bool NA, typename Expr>
        Vector& operator=( const SugarVectorExpression<RTYPE, NA, Expr>& other ){
            assign_expression( other, typename std::is_base_of< VectorOf<RTYPE>, Expr>::type() ) ;
            return *this ;
        }
        
    private:
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other,  std::true_type ){
            data = other.get_ref() ;    
        }
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other, std::false_type ){
            reset(other.size());
            other.apply(*this) ;
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other,  std::true_type ){
            data = other.get_ref() ;    
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other, std::false_type ){
            int n = other.size() ;
            if( n != size() ){
                reset(n) ;    
            }
            other.apply(*this) ;
        }
        
        inline void reset(int n){
            data = Rf_allocVector(RTYPE, n) ;        
        }
        
        inline stored_type* dataptr(){
            return reinterpret_cast<stored_type*>( DATAPTR(data) );    
        }
        inline const stored_type* dataptr() const{
            return reinterpret_cast<const stored_type*>( DATAPTR(data) );    
        }
        
    public:
        inline iterator begin() { return dataptr() ; }
        inline iterator end() { return dataptr() + size() ; }
        
        inline const_iterator begin() const{ return dataptr() ; }
        inline const_iterator end() const{ return dataptr() + size() ; }
        
        inline reference operator[](int i){ return *( dataptr() + i ) ;}
        inline const_reference operator[](int i) const { return *( dataptr() + i ); }
        
        template <typename... Args> static Vector create(Args... args) {
            return typename create_type<RTYPE, Args...>::type( args... ) ;    
        }
    
        inline NameProxy operator[]( const std::string& name ){
            return NameProxy( *this, name ) ;
        }
        inline const NameProxy operator[]( const std::string& name ) const {
            return NameProxy( const_cast<Vector&>(*this), name ) ;
        }
    } ;

    #undef VEC
    
}


#endif
