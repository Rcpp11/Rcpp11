#ifndef Rcpp_Language_h
#define Rcpp_Language_h

namespace Rcpp{ 

    /** 
     * C++ wrapper around calls (LANGSXP SEXP)
     *
     * This represents calls that can be evaluated
     */
    RCPP_API_CLASS(Language_Impl)
        , public DottedPairProxyPolicy<Language_Impl<StoragePolicy>>, 
        public DottedPairImpl<Language_Impl<StoragePolicy>>
    {
    public:
        using Proxy = typename DottedPairProxyPolicy<Language_Impl<StoragePolicy>>::DottedPairProxy ;
        using const_Proxy = typename DottedPairProxyPolicy<Language_Impl<StoragePolicy>>::const_DottedPairProxy ;
        
        RCPP_GENERATE_CTOR_ASSIGN(Language_Impl) 
	
        Language_Impl(){}
        
        
        /**
         * Attempts to convert the SEXP to a call
         *
         * @throw not_compatible if the SEXP could not be converted
         * to a call using as.call
         */
        Language_Impl(SEXP lang){
            Storage::set__( r_cast<LANGSXP>(lang) ) ;
        }
        
        /**
         * Creates a call using the given symbol as the function name
         *
         * @param symbol symbol name to call
         *
         * Language( "rnorm" ) makes a SEXP similar to this (expressed in R)
         * > as.call( as.list( as.name( "rnorm") ) )
         * > call( "rnorm" )
         */
        explicit Language_Impl( const std::string& symbol ){
            Storage::set__( Rf_lang1( Rf_install(symbol.c_str()) ) ) ;
        }

        /**
         * Creates a call using the given symbol as the function name
         *
         * @param symbol symbol name to call
         *
         * Language( Symbol("rnorm") ) makes a SEXP similar to this: 
         * > call( "rnorm" )
         */
        explicit Language_Impl( const Symbol& symbol ){
            Storage::set__( Rf_lang1( symbol ) );    
        }

        /**
         * Creates a call to the function
         * 
         * @param function function to call
         */
        explicit Language_Impl( const Function& function) {
            Storage::set__( Rf_lang1( function ) ) ;
        }
        
        template<typename... Args> 
        Language_Impl( const std::string& symbol, const Args&... args) {
            Storage::set__( language( Rf_install( symbol.c_str() ), args...) ) ;
        }
        template<typename... Args> 
        Language_Impl( const Function& function, const Args&... args) {
            Storage::set__( language( function, args...) ) ;
        }
        
        /**
         * sets the symbol of the call
         */
        void setSymbol( const std::string& symbol){
            setSymbol( Symbol( symbol ) ) ;    
        }

        /**
         * sets the symbol of the call
         */
        void setSymbol( const Symbol& symbol ){
            SEXP data = Storage::get__() ;
            SETCAR( data, symbol ) ;
            SET_TAG(data, R_NilValue);  
        }

        /**
         * eval this call in the global environment
         */
        SEXP eval() const {
            return eval( R_GlobalEnv ) ;    
        }

        /**
         * eval this call in the requested environment
         */
        SEXP eval(SEXP env) const {
            return Rcpp_eval( Storage::get__(), env ) ;
        }

    };
    
    template <
        typename OUT=SEXP, 
        template <class> class StoragePolicy = PreserveStorage
    >
    class fixed_call {
    public:
        typedef OUT result_type ;
        typedef Language_Impl<StoragePolicy> Language ; 
        typedef Function_Impl<StoragePolicy> Function ; 
        
        fixed_call( Language call_ ) : call(call_){}
        fixed_call( Function fun ) : call(fun){}
        
        OUT operator()(){
            return as<OUT>( call.eval() ) ;
        }
        
    private:
        Language call ;
    } ;

    template <typename T, typename OUT = SEXP, 
      template <class> class StoragePolicy = PreserveStorage
    >
    class unary_call : public std::unary_function<T,OUT> {
    public:
        typedef Language_Impl<StoragePolicy> Language ; 
        typedef Function_Impl<StoragePolicy> Function ; 
        
        unary_call( Language call_ ) : call(call_), proxy(call_,1) {}
        unary_call( Language call_, int index ) : call(call_), proxy(call_,index){}
        unary_call( Function fun ) : call( fun, R_NilValue), proxy(call,1) {}
        
        OUT operator()( const T& object ){
            proxy = object ;
            return as<OUT>( call.eval() ) ;
        }
        
    private:
        Language call ;
        typename Language::Proxy proxy ;
    } ;

    template <typename T1, typename T2, 
      typename OUT = SEXP, template <class> class StoragePolicy = PreserveStorage
    >
    class binary_call : public std::binary_function<T1,T2,OUT> {
    public:
        typedef Language_Impl<StoragePolicy> Language ; 
        typedef Function_Impl<StoragePolicy> Function ; 
        
        binary_call( Language call_ ) : call(call_), proxy1(call_,1), proxy2(call_,2) {}
        binary_call( Language call_, int index1, int index2 ) : call(call_), proxy1(call_,index1), proxy2(call_,index2){}
        binary_call( Function fun) : call(fun, R_NilValue, R_NilValue), proxy1(call,1), proxy2(call,2){}
        
        OUT operator()( const T1& o1, const T2& o2 ){
            proxy1 = o1 ;
            proxy2 = o2 ;
            return as<OUT>( call.eval() ) ;
        }
        
    private:
        Language call ;
        typename Language::Proxy proxy1 ;
        typename Language::Proxy proxy2 ;
    } ;

    
} // namespace Rcpp

#endif
