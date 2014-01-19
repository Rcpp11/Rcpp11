#ifndef Rcpp__sugar__self_match_h
#define Rcpp__sugar__self_match_h
          
namespace Rcpp{
namespace sugar{

template <typename HASH, typename STORAGE>
class SelfInserter {
public:
    SelfInserter( HASH& hash_ ) : hash(hash_), index(0) {}
    
    inline int operator()( STORAGE value ){
        typename HASH::iterator it = hash.find( value ) ;
        if( it == hash.end() ){
            hash.insert( std::make_pair(value, ++index) ) ;
            return index ; 
        } else {
            return it->second ;
        }   
    }
    
private:
    HASH& hash ;
    int index;
} ; 

template <int RTYPE, typename TABLE_T>        
class SelfMatch {
public:
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    
    SelfMatch( const TABLE_T& table ): hash(), result(table.size()) {
        std::transform( table.begin(), table.end(), result.begin(), Inserter(hash) ) ;
    }
    
    inline operator IntegerVector() const { return result ; }
    
private:
    typedef std::unordered_map<STORAGE, int> HASH ;
    typedef SelfInserter<HASH,STORAGE> Inserter ;
    HASH hash ; 
    IntegerVector result ;
}; 
    
} // sugar

template <int RTYPE, bool NA, typename T>
inline IntegerVector self_match( const VectorBase<RTYPE,NA,T>& x ){
    Vector<RTYPE> vec(x) ;
    return sugar::SelfHash<RTYPE>(vec).fill_and_self_match() ;
}


} // Rcpp
#endif

