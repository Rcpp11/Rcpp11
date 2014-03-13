#ifndef Rcpp__vector__Matrix_h
#define Rcpp__vector__Matrix_h

namespace Rcpp{

    template <int RTYPE, template <class> class StoragePolicy = PreserveStorage>
    class Matrix {
    private:
        Vector<RTYPE,StoragePolicy> vec ;
        int* dims ;
        
    public:
        using Proxy = typename Vector<RTYPE,StoragePolicy>::Proxy ;
        using const_Proxy = typename Vector<RTYPE,StoragePolicy>::const_Proxy ;
        using iterator = typename Vector<RTYPE,StoragePolicy>::iterator ;
        using const_iterator = typename Vector<RTYPE,StoragePolicy>::const_iterator ;
         
        Matrix(int nr, int nc) : vec(nr, nc){
            set_dims(nr, nc) ;    
        }
        Matrix(int i) : Matrix(i,i){}
        Matrix() : Matrix(0,0){}
        
        Matrix( SEXP x ){
            SEXP d = Rf_getAttrib(x,R_DimSymbol) ;
            if( d == R_NilValue )
                throw not_a_matrix() ;
            vec = x ;
            dims = INTEGER(d) ;
        }
        
        inline int nrow() const {
            return dims[0] ;
        }
        inline int ncol() const {
            return dims[1] ;    
        }
        
        inline iterator begin(){ return vec.begin() ; }
        inline iterator end(){ return vec.end(); }
        
        inline const_iterator begin() const { return vec.begin() ; }
        inline const_iterator end() const { return vec.end(); }
        
        inline Proxy operator()(int i, int j) { return vec[offset(i,j)] ; }
        inline const_Proxy operator()(int i, int j) const { return vec[offset(i,j)] ; }
        
    private:
        
        inline void set_dims(int nr, int nc){
            Armor<SEXP> dim = Rf_getAttrib(vec, R_DimSymbol ) ;
            if( dim == R_NilValue || Rf_length(dim) != 2 ){
                dim = Rf_allocVector(INTSXP, 2 ) ;
                Rf_setAttrib(vec, R_DimSymbol, dim ) ;
            }
            dims = INTEGER(dim) ;
            dims[0] = nr ;
            dims[0] = nc ;
        }
        
        inline int offset(int i, int j) const {
            return i + nrow()*j ;
        }
        
    } ;
    
    typedef Matrix<CPLXSXP> ComplexMatrix ;  
    typedef Matrix<INTSXP>  IntegerMatrix ;
    typedef Matrix<LGLSXP>  LogicalMatrix ;
    typedef Matrix<REALSXP> NumericMatrix ;
    typedef Matrix<REALSXP> DoubleMatrix ;
    typedef Matrix<RAWSXP>  RawMatrix ;
    
    typedef Matrix<STRSXP>  CharacterMatrix ;   
    typedef Matrix<STRSXP>  StringMatrix ;
    typedef Matrix<VECSXP>  GenericMatrix ;
    typedef Matrix<EXPRSXP> ExpressionMatrix ;
    
}

#endif
