#ifndef Rcpp__vector__MatrixRow_h
#define Rcpp__vector__MatrixRow_h

namespace Rcpp{

    template <int RTYPE, typename Mat>
    class MatrixRow : public SugarVectorExpression<RTYPE,true,MatrixRow<RTYPE,Mat>> {
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
            for( int i=0; i<n; i++) {
                at(i) = x[i] ;
            }
        }
        
    };

}

#endif
