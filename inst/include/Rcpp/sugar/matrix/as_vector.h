#ifndef Rcpp__sugar__matrix_as_vector_h
#define Rcpp__sugar__matrix_as_vector_h

namespace Rcpp{	
namespace internal{

template <int RTYPE, bool NA, typename T>
inline Rcpp::Vector<RTYPE> 
as_vector__impl( MatrixBase<RTYPE,NA,T>& t, std::false_type ){
    T& ref = t.get_ref() ;
    int nc = ref.ncol(), nr = ref.nrow() ;
    Vector<RTYPE> out (nr*nc) ;
    int k =0; 
    for( int col_index=0; col_index<nc; col_index++)
        for( int row_index=0; row_index<nr; row_index++, k++)
            out[k] = ref( row_index, col_index ) ;
    
    return out ;
}

template <int RTYPE, bool NA, typename T>
inline Rcpp::Vector<RTYPE> 
as_vector__impl( MatrixBase<RTYPE,NA,T>& t, std::true_type ){
    Matrix<RTYPE>& ref = t.get_ref() ;
    int size = ref.ncol()*ref.nrow() ;
    typename Rcpp::Vector<RTYPE>::iterator first(static_cast<const Rcpp::Vector<RTYPE>&>(ref).begin())  ;
    Vector<RTYPE> res = import(first, first+size );
    return res ;
} 

} // internal
 
template <int RTYPE, bool NA, typename T>
inline Rcpp::Vector<RTYPE> 
as_vector( const MatrixBase<RTYPE,NA,T>& t ){
    return internal::as_vector__impl( const_cast< MatrixBase<RTYPE,NA,T>& >(t), typename std::is_same< T , Matrix<RTYPE> >() ) ;
}

} // Rcpp
#endif

