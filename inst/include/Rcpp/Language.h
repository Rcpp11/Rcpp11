#ifndef Rcpp_Language_h
#define Rcpp_Language_h

namespace Rcpp{ 

    /** 
     * C++ wrapper around calls (LANGSXP SEXP)
     *
     * This represents calls that can be evaluated
     */
    RCPP_API_CLASS(Language_Impl), 
        public DottedPairProxyPolicy<Language_Impl<Storage>>, 
        public DottedPairImpl<Language_Impl<Storage>>
    {
        RCPP_API_IMPL(Language_Impl)
        
        inline void set(SEXP x){
            data = r_cast<LANGSXP>(x) ;    
        }
        
        typedef typename DottedPairProxyPolicy<Language_Impl<Storage>>::DottedPairProxy Proxy;
        
        /**
         * Creates a call to the function
         * 
         * @param function function to call
         */
        explicit Language_Impl( const Function& function) : 
            data( Rf_lang1( function ) ){}
        
        template<typename... Args> 
        Language_Impl( const std::string& symbol, const Args&... args) : 
            data( language( Symbol(symbol), args...) ){}
            
        template<typename... Args> 
        Language_Impl( const Function& function, const Args&... args) : 
            data( language( function, args...)){}
        
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
            return Rcpp_eval( data, env ) ;
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
