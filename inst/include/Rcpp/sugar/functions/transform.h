#ifndef Rcpp__sugar__transform_h
#define Rcpp__sugar__transform_h

namespace Rcpp{
    namespace sugar{
    
        template <typename InputIterator, typename Function>
        class Transform : 
            public SugarVectorExpression<
                typename std::result_of<Function(typename std::iterator_traits<InputIterator>::value_type)>::type, 
                Transform<InputIterator, Function>
            >, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename std::result_of<Function(typename std::iterator_traits<InputIterator>::value_type)>::type value_type ;
            
            Transform( InputIterator begin_, InputIterator end_, Function fun_ ) : begin(begin_), end(end_), fun(fun_){}
            
            inline value_type operator[]( R_xlen_t i) const {
                return fun( * (begin+i) ) ;    
            }
            
            inline R_xlen_t size() const {
                return std::distance(begin, end) ;    
            }
            
            template <typename Target>
            void apply( Target& target ) const {
                std::transform( begin, end, target.begin(), fun ) ;        
            }
            
        private:
            InputIterator begin, end ;
            Function fun ;
        } ;
        
    } // sugar
    
    template <typename InputIterator, typename Function>
    inline sugar::Transform<InputIterator, Function>
    transform( InputIterator begin, InputIterator end, Function fun ){
        return sugar::Transform<InputIterator, Function>( begin, end, fun ) ;    
    }



} // Rcpp
#endif

