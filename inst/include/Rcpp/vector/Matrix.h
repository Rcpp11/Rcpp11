#ifndef Rcpp__vector__Matrix_h
#define Rcpp__vector__Matrix_h

namespace Rcpp{

    template <int RTYPE, template <class> class StoragePolicy>
    class Matrix : public MatrixBase<RTYPE, true, Matrix<RTYPE,StoragePolicy> >{
    private:
        Vector<RTYPE,StoragePolicy> vec ;
        int* dims ;
        
    public:
        using Proxy = typename Vector<RTYPE,StoragePolicy>::Proxy ;
        using const_Proxy = typename Vector<RTYPE,StoragePolicy>::const_Proxy ;
        using iterator = typename Vector<RTYPE,StoragePolicy>::iterator ;
        using const_iterator = typename Vector<RTYPE,StoragePolicy>::const_iterator ;
        
        using Column = MatrixColumn<RTYPE, Matrix> ;
        using Row = MatrixRow<RTYPE, Matrix> ;
        
        Matrix(int nr, int nc) : vec(nr*nc){
            set_dimensions(nr,nc) ;
        }
        
        template <typename U>
        Matrix(int nr, int nc, const U& u) : vec(nr*nc, u){
            set_dimensions(nr,nc) ;
        }
        
        Matrix() : Matrix(0,0){}
        
        Matrix( SEXP x ){
            SEXP d = Rf_getAttrib(x,R_DimSymbol) ;
            if( d == R_NilValue || Rf_length(d) != 2)
                throw not_a_matrix() ;
            vec = x ;
            dims = INTEGER(d) ;
        }
        
        template <bool NA, typename Mat>
        Matrix( const MatrixBase<RTYPE,NA,Mat>& mat ) : Matrix( mat.nrow(), mat.ncol() ) {
            int nr = dims[0] ;
            int nc = dims[1] ;
            for( int j=0, k=0; j<nc; j++){
                for( int i=0; i<nr; i++){
                    vec[k++] = mat(i,j) ;
                }
            }
        }
        
        inline operator SEXP() const { return vec ; }
            
        inline int nrow() const { return dims[0] ; }
        inline int ncol() const { return dims[1] ; }
        inline int size() const { return vec.size() ; }
        
        inline iterator begin(){ return vec.begin() ; }
        inline iterator end(){ return vec.end(); }
                   
        inline const_iterator begin() const { return vec.begin() ; }
        inline const_iterator end() const { return vec.end(); }
              
        inline Proxy operator[](int i){ return vec[i] ; }
        inline const_Proxy operator[](int i) const{ return vec[i] ; }
        
        inline Proxy operator()(int i, int j) { return vec[offset(i,j)] ; }
        inline const_Proxy operator()(int i, int j) const { return vec[offset(i,j)] ; }
        
        inline Column column(int i){ return Column(*this, i) ; }
        inline Column operator()(internal::NamedPlaceHolder, int i){ return column(i); }
        
        inline Row row(int i){ return Row(*this, i) ; }
        inline Row operator()(int i, internal::NamedPlaceHolder){ return row(i); }
        
    private:
        
        inline int offset(int i, int j) const {
            return i + nrow()*j ;
        }
        
        inline void set_dimensions(int nr, int nc){
            Shield<SEXP> dim = Rf_allocVector(INTSXP, 2 ) ;
            dims = INTEGER(dim) ;
            dims[0] = nr ;
            dims[1] = nc ;
            Rf_setAttrib(vec, R_DimSymbol, dim ) ;        
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
