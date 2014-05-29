#ifndef Rcpp__sugar__FunctionWithConversion_h
#define Rcpp__sugar__FunctionWithConversion_h

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
    }
}    

#endif
