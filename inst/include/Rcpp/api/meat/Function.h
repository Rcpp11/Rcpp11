#ifndef Rcpp_api_meat_Function_h
#define Rcpp_api_meat_Function_h

namespace Rcpp{ 

    template <bool fast>
    inline SEXP eval_call( const Language& call ){
        return call.eval() ;
    }
    template <>
    inline SEXP eval_call<true>( const Language& call){
        return call.fast_eval() ;    
    }
    
    template < template <class> class StoragePolicy, bool fast>
    template<typename... Args> 
    SEXP Function_Impl<StoragePolicy, fast>::operator()( const Args&... args) const {
        RCPP_DEBUG( "Function::operator(...) nargs = %d", sizeof...(args)  )
        typedef typename std::tuple<Args...> Tuple ;
        RCPP_DEBUG( "tuple = %s", DEMANGLE(Tuple) )
        Language call( Storage::get__() , args... );
        return eval_call<fast>( call ) ;
    }
    
    template < template <class> class StoragePolicy, bool fast>
    Function_Impl<StoragePolicy, fast>::Function_Impl(SEXP x) {
        RCPP_DEBUG( "Function::Function(SEXP = <%p>)", x)
        switch( TYPEOF(x) ){
        case CLOSXP:
        case SPECIALSXP:
        case BUILTINSXP:
            Storage::set__(x) ;
            break; 
        default:
            throw not_compatible("cannot convert to function") ;
        }
    }
	
    template < template <class> class StoragePolicy, bool fast>
    Function_Impl<StoragePolicy, fast>::Function_Impl(const std::string& name) {
        SEXP nameSym = Rf_install( name.c_str() );	
        Storage::set__( Rf_findFun( nameSym, R_GlobalEnv ) ) ;
    }
	
    template < template <class> class StoragePolicy, bool fast>
    SEXP Function_Impl<StoragePolicy, fast>::environment() const {
        if( TYPEOF(Storage::get__()) != CLOSXP ) {
            throw not_a_closure() ;
        }
        return CLOENV(Storage::get__()) ;
    }
	
    template < template <class> class StoragePolicy, bool fast>
    SEXP Function_Impl<StoragePolicy, fast>::body() const {
        return BODY( Storage::get__() ) ;
    }

    
} // namespace Rcpp

#endif
