#ifndef Rcpp__sugar__seq_along_h
#define Rcpp__sugar__seq_along_h

namespace Rcpp{
namespace sugar{

class SeqLen : public SugarVectorExpression< INTSXP,false,SeqLen > {
public:
    SeqLen( int len_ ) : len(len_){}

    inline int operator[]( int i ) const {
        return 1 + i ;
    }
    inline int size() const { return len ; }

private:
    int len ;
} ;

} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::SeqLen seq_along( const Rcpp::VectorBase<RTYPE,NA,T>& t){
    return sugar::SeqLen( t.size() ) ;
}

inline sugar::SeqLen seq_len( const size_t& n){
    return sugar::SeqLen( n ) ;
}

inline Range seq(int start, int end){
    return Range( start, end ) ;
}


} // Rcpp
#endif

