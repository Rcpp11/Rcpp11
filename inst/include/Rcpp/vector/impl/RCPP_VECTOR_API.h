    RCPP_API_IMPL(Vector)                                                                     
         
    R_xlen_t offset(const std::string& name) const {
        SEXP names = RCPP_GET_NAMES(data) ;
        if( names == R_NilValue ) stop("vector has no names");
        int n = size() ;
    
        SEXP* data = internal::r_vector_start<STRSXP>(names) ;
        int index = std::find( data, data+n, Rf_mkChar(name.c_str()) ) - data ;
        if( index == n ) stop("index out of bounds") ;
        return index ;
    }
        
    inline void set(SEXP x){                                                                  
        set_data(r_cast<RTYPE>(x)) ;                                                           
    }                                                                                         
     
    explicit Vector(R_xlen_t n) {                                                                           
        reset(n) ;                                                                            
    }
    
    #if defined(LONG_VECTOR_SUPPORT)
    explicit Vector(int n) {                                                                           
        reset(n) ;                                                                            
    }                                                                                         
    #endif
                                                                                              
    Vector(){                                                                                 
        reset(0);                                                                             
    }                                                                                         
    template <typename eT, typename Expr>                                                         
    Vector( const SugarVectorExpression<eT, Expr>& other ) { 
        import_expression( other, typename std::is_base_of< VectorOfRTYPE<RTYPE>, Expr>::type() ) ;
    }                                                                                         
                                                                                              
    template <typename eT, typename Expr>                                                         
    Vector& operator=( const SugarVectorExpression<eT, Expr>& other ){    
        assign_expression( other, typename std::is_base_of< VectorOfRTYPE<RTYPE>, Expr>::type() ) ;
        return *this ;                                                                        
    }                                                                                         
                                                                                              
    template <int RT, typename Expr>                                                                  
    Vector( const LazyVector<RT,Expr>& other ) {                                           
        import_applyable(other) ;                                                             
    }                                                                                         
                                                                                              
    template <int RT, typename Expr>                                                                  
    Vector& operator=( const LazyVector<RT,Expr>& other ) {                                
        assign_applyable(other) ;                                                             
        return *this ;                                                                        
    }                                                                                         
    inline value_type* dataptr(){                                                            
        return cache ;
    }                                                                                         
    inline const value_type* dataptr() const{                                                
        return const_cast<const value_type*>(cache) ;
    }                                                                                         
    
    inline NameProxy<Vector> operator[]( const std::string& name){
        return NameProxy<Vector>( *this, name ) ;
    }
    
    inline const NameProxy<Vector> operator[]( const std::string& name) const {
        return NameProxy<Vector>( const_cast<const Vector&>(*this), name ) ;
    }
        
    template <typename... Args> 
    static Vector create(Args&&... args) {
        typedef typename create_type<RTYPE, Args...>::type creator;
        Vector res = creator( std::forward<Args>(args)... ) ;
        return res ;
    }
        
    inline R_xlen_t length() const { return len ; }
    inline R_xlen_t size() const { return len ; }
    
    template <typename eT, typename Expr>
    inline typename subset_proxy_type<Vector,eT,Expr>::type 
    operator[] ( const SugarVectorExpression<eT, Expr>& other) {
        return make_subset_proxy(*this, other);
    }

private:
    value_type* cache ;
    R_xlen_t len ;
    
    inline void set_data(SEXP x){
        set_data(x, get_length(x) ) ; 
    }
    
    inline void set_data(SEXP x, R_xlen_t n){
        data = x ;
        cache = reinterpret_cast<value_type*>(DATAPTR(x)) ;
        len = n ; 
    }
    
    inline R_xlen_t get_length(SEXP x){
        #if defined(LONG_VECTOR_SUPPORT)
            R_xlen_t n = SHORT_VEC_LENGTH(x) ;
            return ( n == R_LONG_VEC_TOKEN ) ? LONG_VEC_LENGTH(x) : n ;
        #else
            return LENGTH(x) ;
        #endif
    }
    
    inline void reset(R_xlen_t n){
        set_data(Rf_allocVector(RTYPE, n), n) ;
    }
    
    template <typename eT, typename Expr>
    inline void import_expression( const SugarVectorExpression<eT,Expr>& other,  std::true_type ){
        set_data( other.get_ref(), other.size() );    
    }
    
    template <typename eT, typename Expr>
    inline void import_expression( const SugarVectorExpression<eT,Expr>& other, std::false_type ){
        import_applyable(other) ;
    }
    
    template <typename T>
    inline void import_applyable( const T& other ){
        reset(other.size());
        other.apply(*this) ;
    }
    
    template <typename eT, typename Expr>
    inline void assign_expression( const SugarVectorExpression<eT, Expr>& other,  std::true_type ){
        set_data( other.get_ref(), other.size() );    
    }
    
    template <typename eT, typename Expr>
    inline void assign_expression( const SugarVectorExpression<eT, Expr>& other, std::false_type ){
        assign_applyable(other) ;    
    }
    
    template <typename T>
    inline void assign_applyable( const T& other ){
        int n = other.size() ;
        if( n != size() ){
            reset(n) ;    
        }
        other.apply(*this) ;
    }

