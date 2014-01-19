#ifndef Rcpp__vector__LazyVector_h
#define Rcpp__vector__LazyVector_h

namespace Rcpp{
namespace internal{
        
template <typename VECTOR>
class LazyVector{
public:
    typedef typename VECTOR::r_type r_type ;
    typedef typename Rcpp::traits::storage_type< r_type::value >::type stored_type ;
        
    LazyVector( const VECTOR& vec_ ) : vec(vec_), n(vec_.size()), data(n), known(n,false){}
                
    inline stored_type operator[]( int i) const {
        stored_type res ;
        if( ! known[i] ) {
            data[i] = res = vec[i] ;
            known[i] = true ;
        } else {
            res = data[i] ;
        }
        return res ;
    }
                
private:
    const VECTOR& vec ;
    int n ;
    mutable std::vector<stored_type> data ;
    mutable std::vector<bool> known ;
} ;

template <int RTYPE>
class LazyVector< Rcpp::Vector<RTYPE> >{
public:
    typedef Rcpp::Vector<RTYPE> VECTOR ;
    typedef typename VECTOR::Proxy Proxy ;
    
    LazyVector( const VECTOR& vec_) : vec(vec_){}
    inline Proxy operator[]( int i) const { return vec[i] ; }
        
private:
    const VECTOR& vec ;
} ;

        
} // internal
} // Rcpp 
#endif
