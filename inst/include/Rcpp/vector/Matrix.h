#ifndef Rcpp__vector__Matrix_h
#define Rcpp__vector__Matrix_h

namespace Rcpp{

template <int RTYPE> 
class Matrix : public Vector<RTYPE>, public MatrixBase<RTYPE,true, Matrix<RTYPE> > {
    int nrows ; 
    
public:
    struct r_type : std::integral_constant<int,RTYPE>{} ;
    struct can_have_na : std::true_type{} ;
    typedef MatrixRow<RTYPE> Row ;
    typedef MatrixColumn<RTYPE> Column ;
    typedef SubMatrix<RTYPE> Sub ;
        
    typedef Vector<RTYPE> VECTOR ;
    typedef typename VECTOR::iterator iterator ;
    typedef typename VECTOR::const_iterator const_iterator ;
    typedef typename VECTOR::converter_type converter_type ;
    typedef typename VECTOR::stored_type stored_type ;
    typedef typename VECTOR::Proxy Proxy ;
    typedef typename VECTOR::const_Proxy const_Proxy ;
    
    Matrix() : VECTOR() {}
        
    Matrix( SEXP x) ;
        
    Matrix( const int& n) ; 
    Matrix( const Dimension& dims)  ;
    Matrix( const int& nrows_, const int& ncols)  ;
        
    template <typename Iterator>
    Matrix( const int& nrows_, const int& ncols, Iterator start ) ;
        
    template <bool NA, typename MAT>
    Matrix( const MatrixBase<RTYPE,NA,MAT>& other )  ;
    
    Matrix( const SubMatrix<RTYPE>& ) ;
    Matrix& operator=( const SubMatrix<RTYPE>& ) ;
   
    inline int ncol() const {
        return VECTOR::dims()[1]; 
    }
    inline int nrow() const {
        return nrows ; 
    }
    inline int cols() const { 
        return VECTOR::dims()[1]; 
    }
    inline int rows() const { 
        return nrows ; 
    }
        
    inline Row row( int i ){ return Row( *this, i ) ; }
    inline Column column( int i ){ return Column(*this, i ) ; }
        
    inline const_iterator begin() const{ return VECTOR::begin() ; }
    inline const_iterator end() const{ return VECTOR::end() ; }
    inline iterator begin() { return VECTOR::begin() ; }
    inline iterator end() { return VECTOR::end() ; }

    inline Proxy operator[]( int i ) ;
    inline const_Proxy operator[]( int i ) const  ;
    
    inline Proxy operator()( const size_t& i, const size_t& j) {
        return VECTOR::at( offset( i, j ) );    
    }
    inline const_Proxy operator()( const size_t& i, const size_t& j) const {
        return VECTOR::at( offset( i, j ) ) ;    
    }
    
    inline Row operator()( int i, internal::NamedPlaceHolder ) ;
    inline Column operator()( internal::NamedPlaceHolder, int i ) ;
    inline Column operator()( internal::NamedPlaceHolder, int i ) const  ;
    inline Sub operator()( const Range& row_range, const Range& col_range) ;        
    inline Sub operator()( internal::NamedPlaceHolder, const Range& col_range) ;
    inline Sub operator()( const Range& row_range, internal::NamedPlaceHolder ) ;
        
    inline int offset( int i, int j) const { 
        return i + nrows * j ;
    }
        
private:
    
    void update_matrix(){
        RCPP_DEBUG( "%s::update_matrix", DEMANGLE(Matrix) ) ;
        VECTOR::update_vector() ;
    }
    
    template <bool NA, typename MAT>
    void import_matrix_expression( const MatrixBase<RTYPE,NA,MAT>& other, int nr, int nc ) ;
        
} ;
}

#endif
