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
        Finalizer( reinterpret_cast<T*>(R_ExternalPtrAddr(p)) ) ;
    }
}

template <                       
    typename T, 
    typename Storage = PreserveStorage, 
    void Finalizer(T*) = standard_delete_finalizer<T> 
>
class XPtr {
    RCPP_API_IMPL(XPtr)
    
    inline void set(SEXP x){
        if( TYPEOF(x) != EXTPTRSXP )
            stop( "expecting an external pointer" ) ;
        data = x ;    
    }
    
    explicit XPtr(SEXP x, SEXP tag, SEXP prot) {
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
        return *(reinterpret_cast<T*>(R_ExternalPtrAddr(data))) ;    
    }
      
    T* operator->() const {
         return reinterpret_cast<T*>(R_ExternalPtrAddr(data));
    }
                
    void setDeleteFinalizer() {
        R_RegisterCFinalizerEx( data, finalizer_wrapper<T,Finalizer> , FALSE) ;     
    }
  
    inline operator T*(){ 
        return reinterpret_cast<T*>(R_ExternalPtrAddr(data)) ;
    }

    TagProxy<XPtr> tag(){
        return TagProxy<XPtr>( *this ) ;
    }
    
    const TagProxy<XPtr> tag() const {
        return TagProxy<XPtr>( const_cast<XPtr&>(*this) ) ;
    }

    ProtectedProxy<XPtr> prot(){
        return ProtectedProxy<XPtr>(*this) ;
    }
    
    const ProtectedProxy<XPtr> prot() const {
        return ProtectedProxy<XPtr>( const_cast<XPtr&>(*this) ) ;
    }

};

} // namespace Rcpp 

#endif
