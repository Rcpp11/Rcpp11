#ifndef Rcpp__vector__MatrixColumn_h
#define Rcpp__vector__MatrixColumn_h

namespace Rcpp{

    template <int RTYPE, typename Mat>
    class MatrixColumn : public SugarVectorExpression<RTYPE,true,MatrixColumn<RTYPE,Mat>> {
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
            if( expr.size() != size() ) throw incompatible_dimensions() ;
            expr.apply(*this) ;
            return *this;
        }
        
        template < template <class> class StoragePolicy >
        MatrixColumn& operator=( const Vector<RTYPE,StoragePolicy>& vec ){
            if( vec.size() != size() ) throw incompatible_dimensions() ;
            std::copy( vec.begin(), vec.end(), begin() );
            return *this;
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
    
    
}
#endif
