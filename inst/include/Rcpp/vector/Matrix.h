#ifndef Rcpp__vector__Matrix_h
#define Rcpp__vector__Matrix_h

namespace Rcpp{

    template <int RTYPE, typename Mat>
    class MatrixColumn : public VectorBase<RTYPE,true,MatrixColumn<RTYPE,Mat>> {
    public:
        using iterator = typename Mat::iterator ;
        using Proxy = typename Mat::Proxy ;
        using const_iterator = typename Mat::const_iterator ;
        using const_Proxy = typename Mat::const_Proxy ;
        
        MatrixColumn( Mat& mat_, int i) : mat(mat_), index(i), n(mat.nrow()){}
        
        MatrixColumn& operator=( const MatrixColumn& other ){
            if( &other != this ){
                std::copy( other.begin(), other.end(), begin() );    
            }
            return *this ;    
        }
        
        template <bool NA, typename Vec>
        MatrixColumn& operator=( const VectorBase<RTYPE,NA,Vec>& expr ){
            iterator start = begin() ;
            for( int i=0; i<n; i++) {
                start[i] = expr[i] ;
            }
            return *this ;    
        }
        
        inline int size() const { return n ;}
        inline Proxy operator[]( int i){ return mat[ index*n + i] ; }
        inline const_Proxy operator[]( int i) const { return mat[ index*n + i] ; }
        
        inline iterator begin() { return mat.begin() + index * n ; }
        inline iterator end(){ return mat.begin() + (index+1)* n ; }
        
        inline const_iterator begin() const { return mat.begin() + index * n ; }
        inline const_iterator end() const { return mat.begin() + (index+1)* n ; }
        
    private:
        Mat& mat ;
        int index ;
        int n ;
    };
    
    template <int RTYPE, typename Mat>
    class MatrixRow : public VectorBase<RTYPE,true,MatrixRow<RTYPE,Mat>> {
    public:
        using Proxy = typename Mat::Proxy ;
        using const_Proxy = typename Mat::const_Proxy ;
        using iterator = StrideIterator<typename Mat::iterator> ;
        using const_iterator = StrideIterator<typename Mat::const_iterator> ; 
        
        MatrixRow( Mat& mat_, int i) : 
            mat(mat_), index(i), n(mat.ncol()), nr(mat.nrow()){}
        
        MatrixRow& operator=( const MatrixRow& other ){
            if( &other != this ){
                import(other) ;       
            }
            return *this ;    
        }
        
        template <bool NA, typename Vec>
        MatrixRow& operator=( const VectorBase<RTYPE,NA,Vec>& expr ){
            import(expr) ;
            return *this ;    
        }
        
        inline int size() const { return n ;}
        
        inline Proxy at(int i){ return mat[ index + i*nr ] ; }
        inline Proxy operator[]( int i){ return at(i) ; }
        
        inline const_Proxy at(int i) const { return mat[ index + i*nr ] ; }
        inline const_Proxy operator[]( int i) const { return at(i) ; }
        
        inline iterator begin() { return iterator( mat.begin() + index, nr ) ; }
        inline iterator end()   { return iterator( mat.begin() + index + n*nr , nr ) ; }
        
        inline const_iterator begin() const { return const_iterator( mat.begin() + index, nr ) ; }
        inline const_iterator end()   const { return const_iterator( mat.begin() + index + n*nr , nr ) ; }
        
    private:
        Mat& mat ;
        int index ;
        int n ;
        int nr ;
        
        template <typename T>
        inline void import( const T& x){
            for( int i=0, k=0; i<n; i++) {
                at(i) = x[i] ;
            }
        }
        
    };
    
    template <int RTYPE, template <class> class StoragePolicy = PreserveStorage>
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
            Shield<SEXP> dim = Rf_allocVector(INTSXP, 2 ) ;
            dims = INTEGER(dim) ;
            dims[0] = nr ;
            dims[1] = nc ;
            Rf_setAttrib(vec, R_DimSymbol, dim ) ;
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
