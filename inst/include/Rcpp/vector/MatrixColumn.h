#ifndef Rcpp__vector__MatrixColumn_h
#define Rcpp__vector__MatrixColumn_h

namespace Rcpp{

    template <int RTYPE, typename Mat>
    class MatrixColumn : public SugarVectorExpression< typename traits::storage_type<RTYPE>::type, MatrixColumn<RTYPE,Mat> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type value_type ;
        typedef typename Mat::iterator iterator;
        typedef typename Mat::const_iterator const_iterator;
        typedef typename Mat::Proxy Proxy ;
        
        MatrixColumn( Mat& mat_, int i) : mat(mat_), index(i), n(mat.nrow()){}
        
        MatrixColumn& operator=( const MatrixColumn& other ){
            if( &other != this ){
                std::copy( other.begin(), other.end(), begin() );    
            }
            return *this ;    
        }
        
        template <typename eT, typename Expr>
        MatrixColumn& operator=( const SugarVectorExpression<eT, Expr>& expr ){
            if( expr.size() != size() ) throw incompatible_dimensions() ;
            expr.apply(*this) ;
            return *this;
        }
         
        inline int size() const { return n ;}
        inline Proxy operator[]( int i){ return mat[ index*n + i] ; }
        inline const Proxy operator[]( int i) const { return mat[ index*n + i] ; }
        
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
