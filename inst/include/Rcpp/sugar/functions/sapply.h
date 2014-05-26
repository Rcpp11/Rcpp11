#ifndef Rcpp__sugar__sapply_h
#define Rcpp__sugar__sapply_h

namespace Rcpp{
    namespace sugar{
             
        template <typename Function, typename input, int RTYPE, typename storage_output_type>
        class FunctionWithConversion {
        public:
            typedef typename Rcpp::traits::r_vector_element_converter<RTYPE>::type converter_type ;
            
            FunctionWithConversion( Function fun_ ) : fun(fun_){}
            
            storage_output_type operator()( input x ) const {
                return converter_type::get( fun(x) ) ;    
            }
            
        private:
            Function fun ;
        } ;
        
        template <typename Function, typename input, int RESULT_R_TYPE>
        struct sapply_function_type {
            typedef typename std::result_of<Function(input)>::type fun_result_type ;
            typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type storage_output_type ;
            
            typedef typename std::conditional< 
                std::is_same<fun_result_type, storage_output_type>::value, 
                Function,
                FunctionWithConversion<Function,input,RESULT_R_TYPE,storage_output_type>
            >::type type ;
        } ;
        
        template <int RTYPE, bool HAS_NA, typename T, typename Function>
        class Sapply : public SugarVectorExpression< 
                Rcpp::traits::r_sexptype_traits<
                    typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type
                >::rtype , 
                true ,
                Sapply<RTYPE,HAS_NA,T,Function>
            >, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename Rcpp::traits::storage_type<RTYPE>::type VEC_STORAGE ;
            typedef typename std::result_of<Function(VEC_STORAGE)>::type fun_result_type ; 
            const static int RESULT_R_TYPE = 
                Rcpp::traits::r_sexptype_traits<fun_result_type>::rtype ;
            typedef typename sapply_function_type<Function,VEC_STORAGE,RESULT_R_TYPE>::type function_type ;
            typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type result_type ;
            
            typedef Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T> input_type ;
            Sapply( const input_type& vec_, Function fun_ ) : vec(vec_), fun(fun_){}
        
            inline result_type operator[]( R_xlen_t i ) const {
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
        
        
        template <int RTYPE1, bool HAS_NA1, int RTYPE2, bool HAS_NA2, typename Function1, typename Function2, typename T2>
        class Sapply< RTYPE1, HAS_NA1, Sapply<RTYPE2, HAS_NA2, T2, Function2>, Function1> : 
            public SugarVectorExpression<
                Rcpp::traits::r_sexptype_traits<
                    typename std::result_of< Function1(typename std::result_of< Function2(typename Rcpp::traits::storage_type<RTYPE2>::type) >::type) >::type
                >::rtype,
                HAS_NA2 || HAS_NA1, 
                Sapply< RTYPE1, HAS_NA1, Sapply<RTYPE2, HAS_NA2, T2, Function2>, Function1>   
            >, 
            public custom_sugar_vector_expression
        {
        public:
            typedef Sapply<RTYPE2, HAS_NA2, T2, Function2> inner ;
            typedef typename inner::input_type input_type ;
            typedef Rcpp::SugarVectorExpression<RTYPE1,HAS_NA1,Sapply<RTYPE2, HAS_NA2, T2, Function2>> outer_input_type ;
            
            typedef Rcpp::functional::Compose<typename inner::function_type,Function1> Function ;
            typedef typename Rcpp::traits::storage_type<RTYPE2>::type VEC_STORAGE ;
            typedef typename std::result_of<Function(VEC_STORAGE)>::type fun_result_type ;
            const static int RESULT_R_TYPE = 
                Rcpp::traits::r_sexptype_traits<fun_result_type>::rtype ;
            typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type result_type ;
            
            typedef typename sapply_function_type<Function,VEC_STORAGE,RESULT_R_TYPE>::type function_type ;
            
            Sapply( const outer_input_type& v, Function1 f1 ) : 
                vec( v.get_ref().vec ), 
                fun( v.get_ref().fun, f1 )
            {}
            
            inline result_type operator[]( R_xlen_t i ) const {
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
        
        
    } // sugar
    
    template <int RTYPE, bool HAS_NA, typename T, typename Function >
    inline sugar::Sapply<RTYPE,HAS_NA,T,Function> sapply( const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& t, Function fun ){
        return sugar::Sapply<RTYPE,HAS_NA,T,Function>( t, fun ) ;
    }

} // Rcpp

#endif
