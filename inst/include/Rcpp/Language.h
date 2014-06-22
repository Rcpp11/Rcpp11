#ifndef Rcpp_Language_h
#define Rcpp_Language_h

namespace Rcpp{ 

    /** 
     * C++ wrapper around calls (LANGSXP SEXP)
     *
     * This represents calls that can be evaluated
     */
    template <typename Storage>
    class Language_Impl: 
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
        Language_Impl( const std::string& symbol, Args&&... args) : 
            data( language( Symbol(symbol), std::forward<Args>(args)...) ){}
            
        template<typename... Args> 
        Language_Impl( const Function& function, Args&&... args) : 
            data( language( function, std::forward<Args>(args)...)){}
        
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
            
        typed_call( Language call_ ) : call(call_){
            for( R_xlen_t i=0; i<n; i++){
                proxies.emplace_back( call, i+1 ) ;
            }
        }
        
        inline OUT operator()( Args&&... args ){
            set__impl( traits::number_to_type<n>(), std::forward<Args>(args)... ) ;
            return as<OUT>( call.eval() ) ;
        }
        
    private:
        const static int n = sizeof...(Args) ;
        Language call ;
        std::vector<Proxy> proxies ;
        
        template <int N, typename First, typename... Types>
        inline void set__impl( traits::number_to_type<N>, const First& first, Types&&... args ){
            proxies[n-N] = first ;
            set_impl( traits::number_to_type<N-1>(), std::forward<Args>(args)...) ;
        }
        
        inline void set_impl( traits::number_to_type<0> ){}
        
    } ;
    
    
} // namespace Rcpp

#endif
