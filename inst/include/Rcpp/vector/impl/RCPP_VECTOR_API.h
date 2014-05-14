#ifndef Rcpp__vector__RCPP_VECTOR_API_h
#define Rcpp__vector__RCPP_VECTOR_API_h

#define RCPP_VECTOR_API(RTYPE)                                                                 \
    friend class CommonVectorMethods<RTYPE,Vector> ;                                           \
                                                                                               \
    using CommonVectorMethods<RTYPE,Vector>::reset ;                                           \
    using CommonVectorMethods<RTYPE,Vector>::import_expression ;                               \
    using CommonVectorMethods<RTYPE,Vector>::import_applyable ;                                \
    using CommonVectorMethods<RTYPE,Vector>::assign_expression ;                               \
    using CommonVectorMethods<RTYPE,Vector>::assign_applyable ;                                \
                                                                                               \
    RCPP_API_IMPL(Vector)                                                                      \
                                                                                               \
    inline void set(SEXP x){                                                                   \
        data = r_cast<RTYPE>( x ) ;                                                            \
    }                                                                                          \
    using VectorOffset<Vector>::size ;                                                         \
                                                                                               \
    Vector(int n) {                                                                            \
        reset(n) ;                                                                             \
    }                                                                                          \
                                                                                               \
    Vector(){                                                                                  \
        reset(0);                                                                              \
    }                                                                                          \
    template <bool NA, typename Expr>                                                          \
    Vector( const SugarVectorExpression<RTYPE,NA,Expr>& other ) {                              \
        import_expression( other, typename std::is_base_of< VectorOf<RTYPE>, Expr>::type() ) ; \
    }                                                                                          \
                                                                                               \
    template <bool NA, typename Expr>                                                          \
    Vector& operator=( const SugarVectorExpression<RTYPE, NA, Expr>& other ){                  \
        assign_expression( other, typename std::is_base_of< VectorOf<RTYPE>, Expr>::type() ) ; \
        return *this ;                                                                         \
    }                                                                                          \
                                                                                               \
    template <typename Expr>                                                                   \
    Vector( const LazyVector<RTYPE,Expr>& other ) {                                            \
        import_applyable(other) ;                                                              \
    }                                                                                          \
                                                                                               \
    template <typename Expr>                                                                   \
    Vector& operator=( const LazyVector<RTYPE,Expr>& other ) {                                 \
        assign_applyable(other) ;                                                              \
        return *this ;                                                                         \
    }                                                                                          \
    inline stored_type* dataptr(){                                                             \
        return reinterpret_cast<stored_type*>( DATAPTR(data) );                                \
    }                                                                                          \
    inline const stored_type* dataptr() const{                                                 \
        return reinterpret_cast<const stored_type*>( DATAPTR(data) );                          \
    }                                                                                          \
    using NameProxyPolicy<VEC>::operator[] ;
                
        

#endif
