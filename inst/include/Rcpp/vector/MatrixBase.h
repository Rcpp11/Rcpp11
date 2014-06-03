#ifndef Rcpp__vector__MatrixBase_h
#define Rcpp__vector__MatrixBase_h

namespace Rcpp{

    template <typename eT, typename Matrix>
    class MatrixBase : public CRTP<Matrix> {
    public:
        using CRTP<Matrix>::get_ref ;
        
        inline const eT operator()(int i, int j) const { 
            return get_ref()(i,j) ; 
        }
        inline eT operator()(int i, int j) { 
            return get_ref()(i,j) ; 
        }
        inline int nrow() const { 
            return get_ref().nrow() ; 
        }
        inline int ncol() const { 
            return get_ref().ncol() ; 
        }
        inline R_xlen_t size() const { 
            return get_ref().size() ; 
        }
        
    } ;
    
}

#endif
