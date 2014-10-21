#ifndef Rcpp__sugar__replicate_h
#define Rcpp__sugar__replicate_h

namespace Rcpp{
    namespace sugar{
    
        template <typename CallType>
        class Replicate : 
            public SugarVectorExpression<
                typename std::result_of<CallType()>::type, 
                Replicate<CallType> 
            >, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename std::result_of<CallType()>::type value_type ;
            typedef replicate_iterator<value_type, CallType> const_iterator ;
            
            Replicate( R_xlen_t n_, CallType call_ ): n(n_), call(call_) {}
            
            inline R_xlen_t size() const { return n ; }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                apply_parallel(target ) ;
            }
            
            template <typename Target>
            inline void apply_serial( Target& target ) const {
                std::generate_n( target.begin(), n, call ) ;  
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                parallel::generate_n( target.begin(), n, call) ;    
            }
            
            inline const_iterator begin() const { return const_iterator( call, 0 ) ; }
            inline const_iterator end() const { return const_iterator( call, size() ) ; }
            
        private:
            R_xlen_t n ;
            CallType call ; 
        } ;
    
        template <typename Function, typename... Args >
        class ReplicateFunctionBinder {
        public:
            typedef typename std::tuple< typename std::decay<Args>::type ...> Tuple ;
            typedef typename Rcpp::traits::index_sequence<Args...>::type Sequence ;
            typedef typename std::result_of<Function(Args...)>::type value_type ;
            
            ReplicateFunctionBinder( Function fun_, Args&&... args) : 
                fun(fun_), tuple( std::forward<Args>(args)...){}
                
            inline value_type operator()() const {
                return apply( Sequence() ) ;        
            }
                
        private:
            Function fun ; 
            Tuple tuple ;
            
            template <int... S>
            inline value_type apply( Rcpp::traits::sequence<S...> ) const {
                return fun( std::get<S>(tuple)... );  
            }
            
        } ;
        
        template <typename Function, typename... Args>
        struct replicate_dispatch_function_type {
            typedef ReplicateFunctionBinder<Function,Args...> type ;
        } ;
        
        template <typename Function>
        struct replicate_dispatch_function_type<Function> {
            typedef Function type ;
        } ;
        
        
        
    } // sugar
    
    template <typename CallType, typename... Args>
    inline auto replicate( R_xlen_t n, CallType call, Args&&... args) -> sugar::Replicate< typename sugar::replicate_dispatch_function_type<CallType,Args...>::type > {
        typedef typename sugar::replicate_dispatch_function_type<CallType,Args...>::type function_type ;
        return sugar::Replicate<function_type>( n, function_type(call,std::forward<Args>(args)...) ) ;    
    }



} // Rcpp
#endif

