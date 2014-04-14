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
        typedef typename DottedPairProxyPolicy<Language_Impl<StoragePolicy>>::DottedPairProxy Proxy;
        typedef typename DottedPairProxyPolicy<Language_Impl<StoragePolicy>>::const_DottedPairProxy const_Proxy;
        
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
    
    
    template <typename OUT = SEXP, typename... Args> 
    class typed_call {
    public:
        typedef Language::Proxy Proxy ;
        
        typed_call( Language call_) : call(call_){
            for( int i=0; i<n; i++){
                proxies.emplace_back( call, i+1 ) ;
            }
        }
        
        inline OUT operator()( const Args&... args ){
            set__impl( traits::number_to_type<n>(), args... ) ;
            return as<OUT>( call.eval() ) ;
        }
        
    private:
        const static int n = sizeof...(Args) ;
        Language call ;
        std::vector<Proxy> proxies ;
        
        template <int N, typename First, typename... Types>
        inline void set__impl( traits::number_to_type<N>, const First& first, const Types&... args ){
            proxies[n-N] = first ;
            set_impl( traits::number_to_type<N-1>(), args...) ;
        }
        
        template <typename First>
        inline void set_impl( traits::number_to_type<1>, const First& first ){
            proxies[n-1] = first ;
        }
        
    } ;
    
    
} // namespace Rcpp

#endif
