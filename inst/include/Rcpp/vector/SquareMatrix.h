#ifndef Rcpp__vector__SquareMatrix_h
#define Rcpp__vector__SquareMatrix_h

namespace Rcpp{

    template <int RTYPE, typename Storage>
    class SquareMatrix : public Matrix<RTYPE, Storage> {
    public:
        using Base = Matrix<RTYPE, Storage> ;
        
        SquareMatrix( int n ) : Base(n,n){}
        
        template <typename U>
        SquareMatrix( int n, const U& u ) : Base(n,n,u){}
        
        SquareMatrix( SEXP x ) : Base(x) {
            if( Base::nrow() != Base::ncol() )
                stop( "not a square matrix : %d x %d", Base::nrow(), Base::ncol() ) ;
        }
        
    } ;
      
    using SquareComplexMatrix     = SquareMatrix<CPLXSXP> ;  
    using SquareIntegerMatrix     = SquareMatrix<INTSXP>  ;
    using SquareLogicalMatrix     = SquareMatrix<LGLSXP>  ;
    using SquareNumericMatrix     = SquareMatrix<REALSXP> ;
    using SquareDoubleMatrix      = SquareMatrix<REALSXP> ;
    using SquareRawMatrix         = SquareMatrix<RAWSXP>  ;
    using SquareCharacterMatrix   = SquareMatrix<STRSXP> ;
    using SquareStringMatrix      = SquareMatrix<STRSXP>  ;
    
}

#endif
