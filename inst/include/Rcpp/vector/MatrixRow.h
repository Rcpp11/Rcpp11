#ifndef Rcpp__vector__MatrixRow_h
#define Rcpp__vector__MatrixRow_h

namespace Rcpp{

    template <int RTYPE, typename Mat>
    class MatrixRow : 
        public SugarVectorExpression<typename Mat::value_type, MatrixRow<RTYPE,Mat>> 
    {
    public:
        typedef typename Mat::Proxy Proxy;
        typedef StrideIterator<typename Mat::iterator> iterator;
        typedef StrideIterator<typename Mat::const_iterator> const_iterator ;
        
        MatrixRow( Mat& mat_, int i) : 
            mat(mat_), index(i), n(mat.ncol()), nr(mat.nrow()){}
        
        MatrixRow& operator=( const MatrixRow& other ){
            if( &other != this ){
                if( other.size() != size() ) throw incompatible_dimensions() ;
                std::copy( other.begin(), other.end(), begin() ) ;
            }
            return *this ;    
        }
        
        template <typename eT, typename Expr>
        MatrixRow& operator=( const SugarVectorExpression<eT, Expr>& expr ){
            if( expr.size() != size() ) throw incompatible_dimensions() ;
            expr.apply(*this) ;
            return *this;    
        }
        
        inline int size() const { return n ;}
        
        inline Proxy operator[]( int i){ return mat[ index + i*nr ] ; }
        inline const Proxy operator[]( int i) const { return mat[ index + i*nr ] ; }
        
        inline iterator begin() { return iterator( mat.begin() + index, nr ) ; }
        inline iterator end()   { return iterator( mat.begin() + index + n*nr , nr ) ; }
        
        inline const_iterator begin() const {
            RCPP_DEBUG( "MatrixRow::begin( mat.begin() = %p, index=%d, nr = %d )", mat.begin(), index, nr ) ;
            return const_iterator( mat.begin() + index, nr ) ; 
        }
        inline const_iterator end() const { 
            RCPP_DEBUG( "MatrixRow::end( mat.begin() = %p, index=%d, nr = %d )", mat.begin(), index, nr ) ;
            return const_iterator( mat.begin() + index + n*nr , nr ) ; 
        }
        
    private:
        Mat& mat ;
        int index ;
        int n ;
        int nr ;
        
    };

}

#endif
