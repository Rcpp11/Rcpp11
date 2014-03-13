#ifndef Rcpp__vector__MatrixBase_h
#define Rcpp__vector__MatrixBase_h

namespace Rcpp{

    template <int RTYPE, bool NA, typename Matrix>
    class MatrixBase {
    public:
        using stored_type  = typename traits::storage_type<RTYPE>::type ;
        struct r_matrix_interface{} ;
        
        const Matrix& get_ref() const { return static_cast<const Matrix&>(*this) ; }
        
        inline stored_type operator()(int i, int j) const { return get_ref()(i,j) ; }
        inline int nrow() const { return get_ref().nrow() ; }
        inline int ncol() const { return get_ref().ncol() ; }
        inline int size() const { return get_ref().size() ; }
    } ;
    
}

#endif
