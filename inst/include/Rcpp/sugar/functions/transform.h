#ifndef Rcpp__sugar__transform_h
#define Rcpp__sugar__transform_h

namespace Rcpp{
    namespace sugar{
    
        template <typename InputIterator, typename Function>
        class Transform : 
            public SugarVectorExpression<
                typename std::result_of<Function(typename std::iterator_traits<InputIterator>::value_type)>::type, 
                Transform<InputIterator, Function>
            >
        {
        public:
            typedef typename std::result_of<Function(typename std::iterator_traits<InputIterator>::value_type)>::type value_type ;
            typedef TransformIterator<value_type,Function,InputIterator> const_iterator ;
            
            Transform( InputIterator begin_, InputIterator end_, Function fun_ ) : src_begin(begin_), src_end(end_), fun(fun_){}
            
            inline R_xlen_t size() const {
                return std::distance(src_begin, src_end) ;    
            }
            
            inline const_iterator begin() const { return const_iterator(fun, src_begin) ; }
            inline const_iterator end() const { return const_iterator(fun, src_end) ; }
            
        private:
            InputIterator src_begin, src_end ;
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

