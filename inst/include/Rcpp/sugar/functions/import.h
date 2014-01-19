#ifndef Rcpp__sugar__import_h
#define Rcpp__sugar__import_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool needs_cast, typename storage_type, typename value_type, typename InputIterator >
    class Import : public Rcpp::VectorBase< RTYPE, true, Import<RTYPE,needs_cast, storage_type, value_type, InputIterator> > {
    public:
        Import( InputIterator begin, size_t n_): n(n_), it(begin) {}
        
        inline storage_type operator[]( int i ) const {
            return *(it + i) ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        InputIterator it ; 
    } ;

    template <int RTYPE, typename storage_type, typename value_type, typename InputIterator >
    class Import<RTYPE,true,storage_type,value_type,InputIterator>  : public Rcpp::VectorBase< RTYPE, true, Import<RTYPE,true, storage_type, value_type, InputIterator> > {
    public:
        Import( InputIterator begin, size_t n_ ): n(n_), it(begin) {}
        
        inline storage_type operator[]( int i ) const {
            return Rcpp::internal::caster<value_type,storage_type>( *(it + i) ) ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        InputIterator it ; 
    } ;

    template <typename InputIterator>
    struct import_type {
        typedef typename std::iterator_traits<InputIterator>::value_type value_type ;
        const static int RTYPE = Rcpp::traits::r_sexptype_traits<value_type>::rtype ;
        typedef typename Rcpp::traits::storage_type<RTYPE>::type storage_type ; 
        typedef typename std::is_same<value_type, storage_type>::type needs_cast_type ;
                
        typedef Import<RTYPE,! needs_cast_type::value,storage_type,value_type, InputIterator> type ;
    } ;
    
} // sugar

template <typename InputIterator>
inline typename sugar::import_type<InputIterator>::type 
import( InputIterator begin, InputIterator end ){
    return typename sugar::import_type<InputIterator>::type( begin, std::distance(begin, end) ) ;    
}

} // Rcpp
#endif

