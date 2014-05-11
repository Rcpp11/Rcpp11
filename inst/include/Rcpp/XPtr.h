#ifndef Rcpp_XPtr_h
#define Rcpp_XPtr_h

namespace Rcpp{
    
template <typename T>
void standard_delete_finalizer(T* obj){
    delete obj ;   
}

template <typename T, void Finalizer(T*) >
void finalizer_wrapper(SEXP p){
    if( TYPEOF(p) == EXTPTRSXP ){
        T* ptr = (T*) R_ExternalPtrAddr(p) ;
        RCPP_DEBUG( "finalizer_wrapper<%s>(SEXP p = <%p>). ptr = %p", DEMANGLE(T), p, ptr  )
        Finalizer(ptr) ;
    }
}

template <                       
    typename T, 
    typename Storage = PreserveStorage, 
    void Finalizer(T*) = standard_delete_finalizer<T> 
>
class XPtr :  
    public SlotProxyPolicy<XPtr<T,Storage,Finalizer>>,    
    public AttributeProxyPolicy<XPtr<T,Storage,Finalizer>>, 
    public ProtectedProxyPolicy<XPtr<T,Storage,Finalizer>>,
    public TagProxyPolicy<XPtr<T,Storage,Finalizer>>, 
    public AttributesProxyPolicy<XPtr<T,Storage,Finalizer>>, 
    public RObjectMethods<XPtr<T,Storage,Finalizer>>
{
    RCPP_API_IMPL(XPtr)
    
    inline void set(SEXP x){
        if( TYPEOF(x) != EXTPTRSXP )
            throw ::Rcpp::not_compatible( "expecting an external pointer" ) ;
        data = x ;    
    }
    
    explicit XPtr(SEXP x, SEXP tag = R_NilValue, SEXP prot = R_NilValue) {
        R_SetExternalPtrTag( x, tag ) ;
        R_SetExternalPtrProtected( x, prot ) ;
        set(x) ;
    }
    
    explicit XPtr(T* p, bool set_delete_finalizer = true, SEXP tag = R_NilValue, SEXP prot = R_NilValue){
        data = R_MakeExternalPtr( (void*)p , tag, prot) ;
        if( set_delete_finalizer ){
            setDeleteFinalizer() ;
        }
    }

    T& operator*() const {
        return *((T*)R_ExternalPtrAddr( data )) ;    
    }
      
    T* operator->() const {
         return (T*)(R_ExternalPtrAddr(data));
    }
                
    void setDeleteFinalizer() {
        R_RegisterCFinalizerEx( data, finalizer_wrapper<T,Finalizer> , FALSE) ;     
    }
  
    inline operator T*(){ 
        return (T*)( R_ExternalPtrAddr(data)) ;
    }

};

} // namespace Rcpp 

#endif
