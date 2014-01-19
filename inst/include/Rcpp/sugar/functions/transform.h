#ifndef Rcpp__sugar__transform_h
#define Rcpp__sugar__transform_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool needs_cast, typename storage_type, typename value_type, typename result_type, typename InputIterator, typename Func >
    class Transform : public Rcpp::VectorBase< RTYPE, true, Transform<RTYPE,needs_cast, storage_type, value_type, result_type, InputIterator, Func> > {
    public:
        Transform( InputIterator begin, Func func_, size_t n_ ): n(n_), it(begin), func(func_) {}
        
        inline storage_type operator[]( int i ) const {
            return func( *(it + i) ) ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        InputIterator it ;
        Func func ;
    } ;

    template <int RTYPE, typename storage_type, typename value_type, typename result_type, typename InputIterator, typename Func >
    class Transform<RTYPE,true,storage_type,value_type,result_type,InputIterator,Func> : public Rcpp::VectorBase< RTYPE, true, Transform<RTYPE, true, storage_type, value_type, result_type, InputIterator, Func> > {
    public:
        Transform( InputIterator begin, Func func_, size_t n_ ): n(n_), it(begin), func(func_) {}
        
        inline storage_type operator[]( int i ) const {
            return Rcpp::internal::caster<result_type,storage_type>( func( *(it + i) ) ) ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        InputIterator it ;
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

