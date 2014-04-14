#ifndef Rcpp__vector__Matrix_h
#define Rcpp__vector__Matrix_h

namespace Rcpp{

    template <int RTYPE, template <class> class StoragePolicy>
    class Matrix : public MatrixBase<RTYPE, true, Matrix<RTYPE,StoragePolicy> >{
    private:
        Vector<RTYPE,StoragePolicy> vec ;
        int* dims ;
        
    public:
        typedef typename Vector<RTYPE,StoragePolicy>::Proxy Proxy;
        typedef typename Vector<RTYPE,StoragePolicy>::const_Proxy const_Proxy;
        typedef typename Vector<RTYPE,StoragePolicy>::iterator iterator;
        typedef typename Vector<RTYPE,StoragePolicy>::const_iterator const_iterator;
        
        typedef MatrixColumn<RTYPE, Matrix> Column;
        typedef MatrixRow<RTYPE, Matrix> Row;
        
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
        
        Matrix( const Matrix& other ) = default ;
        Matrix& operator=( const Matrix& ) = default ;
            
        template <bool NA, typename Expr>
        Matrix( const SugarMatrixExpression<RTYPE,NA,Expr>& expr ) : Matrix( expr.nrow(), expr.ncol() ) {
            expr.apply(*this) ;
        }
        template <bool NA, typename Expr>
        Matrix& operator=( const SugarMatrixExpression<RTYPE,NA,Expr>& expr ) {
            if( nrow() != expr.nrow() || ncol() != expr.ncol() ) throw incompatible_dimensions() ;
            expr.apply(*this) ;
            return *this ;
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
