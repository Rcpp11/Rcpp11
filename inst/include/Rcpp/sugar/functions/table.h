#ifndef Rcpp__sugar__table_h
#define Rcpp__sugar__table_h
          
namespace Rcpp{
namespace sugar{

template <typename HASH, typename STORAGE>
class CountInserter {
public:
    CountInserter( HASH& hash_ ) : hash(hash_), index(0) {}
    
    inline void operator()( STORAGE value ){
        hash[value]++ ;
    }
    
private:
    HASH& hash ;
    int index;
} ; 

template <typename HASH, int RTYPE>
class Grabber{
public:
    Grabber( IntegerVector& res_, CharacterVector& names_ ) : res(res_), names(names_), index(0){}
    
    template <typename T>
    inline void operator()( T pair){
        res[index] = pair.second ;
        names[index++] = internal::r_coerce<RTYPE,STRSXP>(pair.first) ;
    }
    
private:
    IntegerVector& res ;
    CharacterVector& names ;
    int index ;
} ;

template <int RTYPE, typename TABLE_T>        
class Table {
public:
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    
    Table( const TABLE_T& table ): hash(), map() {
        // populate the initial hash
        std::for_each( table.begin(), table.end(), Inserter(hash) ) ;
        
        // populate the map, sorted by keys
        map.insert( hash.begin(), hash.end() ) ;
    }
    
    inline operator IntegerVector() const { 
        // fill the result
        int n = map.size() ;
        IntegerVector result(n) ;
        CharacterVector names(n) ;
        std::for_each( map.begin(), map.end(), Grabber<SORTED_MAP,RTYPE>(result, names) ) ;
        result.names() = names ;
        return result ;
    }
    
private:
    typedef std::unordered_map<STORAGE, int> HASH ;
    typedef CountInserter<HASH,STORAGE> Inserter ;
    
    typedef std::map<STORAGE, int, typename Rcpp::traits::comparator_type<RTYPE>::type > SORTED_MAP ;
    
    HASH hash ;
    SORTED_MAP map ;
}; 
    
} // sugar

template <int RTYPE, bool NA, typename T>
inline IntegerVector table( const SugarVectorExpression<RTYPE,NA,T>& x ){
    return sugar::Table<RTYPE,T>(x.get_ref()) ;
}


} // Rcpp
#endif

