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
    template <class> class StoragePolicy = PreserveStorage, 
    void Finalizer(T*) = standard_delete_finalizer<T> 
>
class XPtr :  
    public StoragePolicy<XPtr<T,StoragePolicy,Finalizer>>,     
    public SlotProxyPolicy<XPtr<T,StoragePolicy,Finalizer>>,    
    public AttributeProxyPolicy<XPtr<T,StoragePolicy,Finalizer>>, 
    public ProtectedProxyPolicy<XPtr<T,StoragePolicy,Finalizer>>,
    public TagProxyPolicy<XPtr<T,StoragePolicy,Finalizer>>, 
    public AttributesProxyPolicy<XPtr<T,StoragePolicy,Finalizer>>, 
    public RObjectMethods<XPtr<T,StoragePolicy,Finalizer>>
{
public:  
    
    RCPP_GENERATE_CTOR_ASSIGN(XPtr)
    
    explicit XPtr(SEXP x, SEXP tag = R_NilValue, SEXP prot = R_NilValue) {
        if( TYPEOF(x) != EXTPTRSXP )
            throw ::Rcpp::not_compatible( "expecting an external pointer" ) ;
        Storage::set__(x) ;
        R_SetExternalPtrTag( x, tag ) ;
        R_SetExternalPtrProtected( x, prot ) ;
    }
	
    explicit XPtr(T* p, bool set_delete_finalizer = true, SEXP tag = R_NilValue, SEXP prot = R_NilValue){
        RCPP_DEBUG( "XPtr(T* p = <%p>, bool set_delete_finalizer = %s, SEXP tag = R_NilValue, SEXP prot = R_NilValue)", p, ( set_delete_finalizer ? "true" : "false" ) )
        Storage::set__( R_MakeExternalPtr( (void*)p , tag, prot) ) ;
        if( set_delete_finalizer ){
            setDeleteFinalizer() ;
        }
    }

    T& operator*() const {
        return *((T*)R_ExternalPtrAddr( Storage::get__() )) ;    
    }
  	
    T* operator->() const {
         return (T*)(R_ExternalPtrAddr(Storage::get__()));
    }
  		  	
    void setDeleteFinalizer() {
        R_RegisterCFinalizerEx( Storage::get__(), finalizer_wrapper<T,Finalizer> , FALSE) ;     
    }
  
    inline operator T*(){ 
        return (T*)( R_ExternalPtrAddr(Storage::get__())) ;
    }

};

} // namespace Rcpp 

#endif
