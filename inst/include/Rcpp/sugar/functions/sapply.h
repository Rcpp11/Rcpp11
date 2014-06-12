#ifndef Rcpp__sugar__sapply_h
#define Rcpp__sugar__sapply_h

namespace Rcpp{
    namespace sugar{
        
        template <typename Function, typename Target, typename input_type>
        struct function_wrapper {
            const static int RTYPE = Target::r_type::value ;
            typedef typename traits::r_vector_element_converter<RTYPE>::type converter ;
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
                
            function_wrapper( Function fun_ ) : fun(fun_){}
            
            inline STORAGE operator()( input_type x ) const {
                if( x == NA ) return NA ;
                return converter::get(fun(x)) ;    
            }
            
            Function fun; 
        } ;
        
        template <typename Function, typename Target, typename input_type>
        struct function_wrapper_notest {
            const static int RTYPE = Target::r_type::value ;
            typedef typename traits::r_vector_element_converter<RTYPE>::type converter ;
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
                
            function_wrapper_notest( Function fun_ ) : fun(fun_){}
            
            inline STORAGE operator()( input_type x ) const {
                return converter::get(fun(x)) ;    
            }
            
            Function fun; 
        } ;
        
        template <typename Function, typename Target, typename input_type>
        struct function_wrapper_type {
            typedef typename std::conditional<
                std::is_same<input_type,bool>::value || std::is_same<input_type,double>::value,
                function_wrapper_notest<Function,Target,input_type>,
                function_wrapper<Function,Target,input_type>
            >::type type ;
        } ;
        
        template <typename eT, typename Expr, typename Function>
        class Sapply : 
            public SugarVectorExpression<
                typename std::result_of<Function(eT)>::type,
                Sapply<eT,Expr,Function>
            >, public custom_sugar_vector_expression
        {
        public:
            typedef Function function_type ;
            typedef typename std::result_of<Function(eT)>::type value_type ; 
            typedef TransformIterator<value_type, function_type, typename Expr::const_iterator > const_iterator ;
            
            Sapply( const SugarVectorExpression<eT, Expr>& vec_, Function fun_ ) : 
                vec(vec_), fun(fun_){}
        
            inline R_xlen_t size() const { 
                return vec.size() ; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(vec), sugar_end(vec), target.begin(), 
                    typename function_wrapper_type<function_type, Target, eT>::type(fun)
                );
            }
            
            inline const_iterator begin() const { return const_iterator( fun, sugar_begin(vec) ) ; }
            inline const_iterator end() const { return const_iterator( fun, sugar_end(vec) ) ; }
            
            const SugarVectorExpression<eT, Expr>& vec ;
            function_type fun ;
        
        } ;
        
        
        template <typename T1, typename T2, typename Expr, typename Function1, typename Function2>
        class Sapply< T1, Sapply<T2, Expr, Function2>, Function1> : 
            public SugarVectorExpression< T1, Sapply< T1, Sapply<T2, Expr, Function2>, Function1> >, 
            public custom_sugar_vector_expression
        {
        public:
            
            typedef Rcpp::functional::Compose<Function2,Function1> function_type ;
            typedef SugarVectorExpression< T2, Sapply<T2, Expr, Function2> > outer_input_type ;
            typedef typename std::result_of<function_type(T2)>::type value_type ;
            typedef Expr expr_type ;
            typedef TransformIterator<value_type, function_type, typename Expr::const_iterator > const_iterator ;
            
            Sapply( const SugarVectorExpression< T1, Sapply< T1, Sapply<T2, Expr, Function2>, Function1> >& v, Function1 f1 ) : 
                vec( v.get_ref().vec ), 
                fun( v.get_ref().fun, f1 )
            {}
            
            inline R_xlen_t size() const { return vec.size() ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(vec), sugar_end(vec), target.begin(), 
                    typename function_wrapper_type<function_type, Target, T2>::type(fun)
                );
            }
            
            inline const_iterator begin() const { return const_iterator( fun, sugar_begin(vec) ) ; }
            inline const_iterator end() const { return const_iterator( fun, sugar_end(vec) ) ; }
            
            const SugarVectorExpression<T2, Expr>& vec ;
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
                
            inline value_type operator()( T x ) const {
                return apply( x, Sequence() ) ;        
            }
                
        private:
            Function fun ; 
            Tuple tuple ;
            
            template <int... S>
            inline value_type apply( T x, Rcpp::traits::sequence<S...> ) const {
                return fun( x, std::get<S>(tuple)... );  
            }
            
        } ;
        
        template <typename Function, typename T, typename... Args>
        struct sugar_dispatch_function_type {
            typedef SapplyFunctionBinder<Function,T,Args...> type ;
        } ;
        
        template <typename Function, typename T>
        struct sugar_dispatch_function_type<Function,T> {
            typedef Function type ;
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr, typename Function, typename... Args >
    inline sugar::Sapply<eT, Expr,typename sugar::sugar_dispatch_function_type<Function, eT, Args...>::type >
    sapply( const SugarVectorExpression<eT,Expr>& expr, Function fun, Args&&... args ) {
        typedef typename sugar::sugar_dispatch_function_type<Function, eT, Args...>::type op ; 
        return sugar::Sapply<eT, Expr, op>( expr, op( fun, std::forward<Args>(args)... ) ) ;
    }

} // Rcpp

#endif
