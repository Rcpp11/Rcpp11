    RCPP_API_IMPL(Vector)                                                                     
         
    inline R_len_t length() const { return ::Rf_length(data) ; }
    inline R_len_t size() const { return length() ; }
    
    R_len_t offset(const std::string& name) const {
        SEXP names = RCPP_GET_NAMES(data) ;
        if( names == R_NilValue ) throw index_out_of_bounds();
        int n = size() ;
    
        SEXP* data = internal::r_vector_start<STRSXP>(names) ;
        int index = std::find( data, data+n, Rf_mkChar(name.c_str()) ) - data ;
        if( index == n ) throw index_out_of_bounds() ;
        return index ;
    }
        
    inline void set(SEXP x){                                                                  
        data = r_cast<RTYPE>( x ) ;                                                           
    }                                                                                         
                                                                                              
    Vector(int n) {                                                                           
        reset(n) ;                                                                            
    }                                                                                         
                                                                                              
    Vector(){                                                                                 
        reset(0);                                                                             
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
                                                                                              
    template <int RT, typename Expr>                                                                  
    Vector( const LazyVector<RT,Expr>& other ) {                                           
        import_applyable(other) ;                                                             
    }                                                                                         
                                                                                              
    template <int RT, typename Expr>                                                                  
    Vector& operator=( const LazyVector<RT,Expr>& other ) {                                
        assign_applyable(other) ;                                                             
        return *this ;                                                                        
    }                                                                                         
    inline stored_type* dataptr(){                                                            
        return reinterpret_cast<stored_type*>( DATAPTR(data) );                               
    }                                                                                         
    inline const stored_type* dataptr() const{                                                
        return reinterpret_cast<const stored_type*>( DATAPTR(data) );                         
    }                                                                                         
    using NameProxyPolicy<VEC>::operator[] ;

    template <typename... Args> 
    static Vector create(Args... args) {
        typedef typename create_type<RTYPE, Args...>::type creator;
        Vector res = creator( args... ) ;
        return res ;
    }
        
private:
    inline void reset(int n){
        data = Rf_allocVector(RTYPE, n) ;        
    }
    
    template <bool NA, typename Expr>
    inline void import_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other,  std::true_type ){
        data = other.get_ref() ;    
    }
    
    template <bool NA, typename Expr>
    inline void import_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other, std::false_type ){
        import_applyable(other) ;
    }
    
    template <typename T>
    inline void import_applyable( const T& other ){
        reset(other.size());
        other.apply(*this) ;
    }
    
    template <bool NA, typename Expr>
    inline void assign_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other,  std::true_type ){
        data = other.get_ref() ;    
    }
    
    template <bool NA, typename Expr>
    inline void assign_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other, std::false_type ){
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

