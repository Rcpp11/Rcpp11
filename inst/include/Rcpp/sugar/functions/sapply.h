#ifndef Rcpp__sugar__sapply_h
#define Rcpp__sugar__sapply_h

namespace Rcpp{
    namespace sugar{
             
        template <typename Expr, typename Function>
        class Sapply : 
            public SugarVectorExpression<Sapply<Expr,Function>>, 
            public custom_sugar_vector_expression
        {
        public:
            typedef Function function_type ;
            typedef 
            typedef typename Expr::value_type vec_storage ;
            typedef typename std::result_of<Function(vec_storage)>::type value_type ; 
            
            Sapply( const SugarVectorExpression<Expr>& vec_, Function fun_ ) : 
                vec(vec_), fun(fun_){}
        
            inline value_type operator[]( R_xlen_t i ) const {
                return fun( vec[i] ) ;
            }
            inline R_xlen_t size() const { 
                return vec.size() ; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(vec), sugar_end(vec), target.begin(), fun ) ;
            }
            
            const SugarVectorExpression<Expr>& vec ;
            function_type fun ;
        
        } ;
        
        
        template <typename Expr, typename Function1, typename Function2>
        class Sapply< Sapply<Expr, Function2>, Function1> : 
            public SugarVectorExpression< Sapply< Sapply<Expr, Function2>, Function1> >, 
            public custom_sugar_vector_expression
        {
        public:
            
            typedef Rcpp::functional::Compose<Function2,Function1> function_type ;
            typedef SugarVectorExpression< Sapply<Expr, Function2> > outer_input_type ;
            typedef std::result_of<function_type(typename Expr::value_type)>::type value_type ;
            
            Sapply( const SugarVectorExpression< Sapply<Expr, Function2> >& v, Function1 f1 ) : 
                vec( v.get_ref().vec ), 
                fun( v.get_ref().fun, f1 )
            {}
            
            inline value_type operator[]( R_xlen_t i ) const {
                return fun( vec[i] ) ;
            }
            inline R_xlen_t size() const { return vec.size() ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(vec), sugar_end(vec), target.begin(), fun ) ;     
            }
            
            const input_type& vec ;
            function_type fun ;
        } ;
    
        
        template <typename Function, typename T, typename... Args >
        class SapplyFunctionBinder {
        public:
            typedef typename std::tuple< typename std::decay<Args>::type ...> Tuple ;
            typedef typename Rcpp::traits::index_sequence<Args...>::type Sequence ;
            typedef typename std::result_of<Function(T,Args...)>::type value_type ;
            
            SapplyFunctionBinder( Function fun_, Args&&... args) : 
                fun(fun_), tuple( std::forward<Args>(args)...){}
                
            inline value_type operator()( storage_type x ) const {
                return apply( x, Sequence() ) ;        
            }
                
        private:
            Function fun ; 
            Tuple tuple ;
            
            template <int... S>
            inline fun_result_type apply( storage_type x, Rcpp::traits::sequence<S...> ) const {
                return fun( x, std::get<S>(tuple)... );  
            }
            
        } ;
        
        template <typename Function, typename T, typename... Args>
        struct sugar_dispatch_function_type {
            typedef SapplyFunctionBinder<Function,Args...> type ;
        } ;
        
        template <typename Function, typename T>
        struct sugar_dispatch_function_type<Function,T> {
            typedef Function type ;
        } ;
        
    } // sugar
    
    template <typename Expr, typename Function, typename... Args >
    inline sugar::Sapply<Expr,typename sugar::sugar_dispatch_function_type<Function,typename Expr::value_type, Args...>::type >
    sapply( const SugarVectorExpression<Expr>& expr, Function fun, Args&&... args ) {
        typedef typename sugar::sugar_dispatch_function_type<Function,typename Expr::value_type, Args...>::type op ; 
        return sugar::Sapply<Expr,op>( expr, op( fun, std::forward<Args>(args)... ) ) ;
        ) ;
    }

} // Rcpp

#endif
