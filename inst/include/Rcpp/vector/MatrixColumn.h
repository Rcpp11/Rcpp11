#ifndef Rcpp__vector__MatrixColumn_h
#define Rcpp__vector__MatrixColumn_h
 
namespace Rcpp{
    
template <int RTYPE>
class MatrixColumn : public VectorBase<RTYPE,true,MatrixColumn<RTYPE> > {
public:
    typedef Matrix<RTYPE> MATRIX ;
    typedef typename MATRIX::Proxy Proxy ;
    typedef typename MATRIX::const_Proxy const_Proxy ;
    typedef typename MATRIX::value_type value_type ;
    typedef typename MATRIX::iterator iterator ;
    typedef typename MATRIX::const_iterator const_iterator ;
        
    MatrixColumn( MATRIX& parent, int i ) : 
        n(parent.nrow()),
        start(parent.begin() + i * n ), 
        const_start(const_cast<const MATRIX&>(parent).begin() + i *n)
    {
        if( i < 0 || i >= parent.ncol() ) throw index_out_of_bounds() ;
    }
    
    MatrixColumn( const MATRIX& parent, int i ) : 
        n(parent.nrow()),
        start(parent.begin() + i * n ), 
        const_start(parent.begin() + i *n)
    {
        if( i < 0 || i >= parent.ncol() ) throw index_out_of_bounds() ;
    }
        
    MatrixColumn( const MatrixColumn& other ) : 
        n(other.n), 
        start(other.start),
        const_start(other.const_start) {}
        
    template <int RT, bool NA, typename T>
    MatrixColumn& operator=( const Rcpp::VectorBase<RT,NA,T>& rhs ){
        const T& ref = rhs.get_ref() ;
        RCPP_LOOP_UNROLL(start,ref)
        return *this ;
    }
        
    MatrixColumn& operator=( const MatrixColumn& rhs ){
        iterator rhs_start = rhs.start ; 
        RCPP_LOOP_UNROLL(start,rhs_start)
        return *this ;
    }

    inline Proxy operator[]( int i ){
        return start[i] ;
    }
        
    inline const_Proxy operator[]( int i ) const {
        return const_start[i] ;
    }
        
    inline iterator begin(){
        return start ;
    }
        
    inline const_iterator begin() const {
        return const_start ;
    }
        
    inline iterator end(){
        return start + n ;
    }
        
    inline const_iterator end() const {
        return const_start + n ;
    }
        
    inline R_len_t size() const {
        return n ;
    }
     
private:
    const R_len_t n ;
    iterator start ;
    const_iterator const_start ;
    
} ;
}

#endif
