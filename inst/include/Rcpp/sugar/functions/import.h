#ifndef Rcpp__sugar__import_h
#define Rcpp__sugar__import_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool needs_cast, typename storage_type, typename value_type, typename InputIterator >
    class Import : 
        public SugarVectorExpression< RTYPE, true, Import<RTYPE,needs_cast, storage_type, value_type, InputIterator> >, 
        public custom_sugar_vector_expression
    {
    public:
        Import( InputIterator begin_, InputIterator end_ ): begin(begin_), end(end_), n( std::distance(begin, end) ){}
        
        inline storage_type operator[]( R_xlen_t i ) const {
            return *(begin + i) ;
        }
        inline int size() const { return n ; }
        
        template <typename Target>
        inline void apply( Target& target ) const {
            std::copy( begin, end, target.begin() ) ;     
        }
        
    private:
        
        InputIterator begin, end ;
        size_t n ; 
    } ;

    template <int RTYPE, typename storage_type, typename value_type, typename InputIterator >
    class Import<RTYPE,true,storage_type,value_type,InputIterator>  : 
        public SugarVectorExpression< RTYPE, true, Import<RTYPE,true, storage_type, value_type, InputIterator> >, 
        public custom_sugar_vector_expression
    {
    public:
        Import( InputIterator begin_, InputIterator end_ ): begin(begin_), end(end_), n( std::distance(begin, end) ){}
        
        inline storage_type operator[]( R_xlen_t i ) const {
            return Rcpp::internal::caster<value_type,storage_type>( *(begin + i) ) ;
        }
        inline int size() const { return n ; }
        
        template <typename Target>
        inline void apply( Target& target ) const {
            std::transform( begin, end, target.begin(), internal::caster<value_type,storage_type> ) ;     
        }
        
    private:
        InputIterator begin, end ;
        size_t n ;
         
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

