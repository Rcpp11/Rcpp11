#ifndef Rcpp__sugar__transform_h
#define Rcpp__sugar__transform_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool needs_cast, typename storage_type, typename value_type, typename result_type, typename InputIterator, typename Func >
    class Transform : 
        public SugarVectorExpression< RTYPE, true, Transform<RTYPE,needs_cast, storage_type, value_type, result_type, InputIterator, Func> >, 
        public custom_sugar_vector_expression {
    public:
        Transform( InputIterator begin_, InputIterator end_, Func func_, size_t n_ ): 
            begin(begin_), end(end_), n(std::distance(begin, end)), func(func_) {}
        
        inline storage_type operator[]( R_xlen_t i ) const {
            return func( *(begin + i) ) ;
        }
        inline R_xlen_t size() const { return n ; }
        
        template <typename Target>
        inline void apply( Target& target ) const {
            std::transform( begin, end, target.begin(), func ) ;     
        }
        
    private:
        InputIterator begin, end ;
        
        size_t n ;
        Func func ;
    } ;

    template <int RTYPE, typename storage_type, typename value_type, typename result_type, typename InputIterator, typename Func >
    class Transform<RTYPE,true,storage_type,value_type,result_type,InputIterator,Func> : 
        public SugarVectorExpression< RTYPE, true, Transform<RTYPE, true, storage_type, value_type, result_type, InputIterator, Func> >,
        public custom_sugar_vector_expression {
    public:
        Transform( InputIterator begin_, InputIterator end_, Func func_, size_t n_ ): 
            begin(begin_), end(end_), n(std::distance(begin, end)), func(func_) {}
        
        inline storage_type operator[]( R_xlen_t i ) const {
            return Rcpp::internal::caster<result_type,storage_type>( func( *(begin + i) ) ) ;
        }
        inline R_xlen_t size() const { return n ; }
        
        template <typename Target>
        inline void apply( Target& target ) const {
            std::transform( begin, end, target.begin(), 
                [this](value_type x){ 
                    return Rcpp::internal::caster<result_type,storage_type>(func(x)); 
                }
            ) ;     
        }
        
    private:
        InputIterator begin, end ;
        
        size_t n ;
        Func func ;
    } ;

     
    template <typename InputIterator, typename Func>
    struct import_transform_type {
        typedef typename std::iterator_traits<InputIterator>::value_type value_type ;
        typedef typename std::result_of<Func(value_type)>::type result_type ;
        
        const static int RTYPE = Rcpp::traits::r_sexptype_traits<result_type>::rtype ;
        typedef typename Rcpp::traits::storage_type<RTYPE>::type storage_type ; 
        typedef typename std::is_same<result_type, storage_type>::type needs_cast_type ;
                
        typedef Transform<RTYPE,!needs_cast_type::value,storage_type,value_type, result_type, InputIterator, Func> type ;
    } ;
    
} // sugar

template <typename InputIterator, typename Func>
inline typename sugar::import_transform_type<InputIterator,Func>::type 
transform( InputIterator begin, InputIterator end, Func func ){
    return typename sugar::import_transform_type<InputIterator,Func>::type( begin, func, std::distance(begin, end) ) ;    
}



} // Rcpp
#endif

