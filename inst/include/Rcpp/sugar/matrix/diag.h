#ifndef Rcpp__sugar__diag_h
#define Rcpp__sugar__diag_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T>
        class Diag_Extractor : public SugarVectorExpression< RTYPE ,NA, Diag_Extractor<RTYPE,NA,T> > {
        public:
            typedef typename Rcpp::MatrixBase<RTYPE,NA,T> MAT_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
            Diag_Extractor( const MAT_TYPE& object_ ) : object(object_), n(0) {
                int nr = object.nrow() ;
                int nc = object.ncol() ;
                n = (nc < nr ) ? nc : nr ;
            }
        
            inline STORAGE operator[]( int i ) const {
                return object( i, i ) ;
            }
            inline int size() const { return n; }
        
        private:
            const MAT_TYPE& object ;
            int n ;
        } ;
        
        
        template <int RTYPE, bool NA, typename T>
        class Diag_Maker : 
            public Rcpp::SugarMatrixExpression< RTYPE ,NA, Diag_Maker<RTYPE,NA,T> >, 
            public custom_sugar_matrix_expression {
        public:
            typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
            Diag_Maker( const VEC_TYPE& object_ ) : object(object_), n(object_.size()) {}
        
            inline STORAGE operator()( int i, int j ) const {
                return (i==j) ? object[i] : 0 ;
            }
            inline int size() const { return n * n; }
            inline int ncol() const { return n; }
            inline int nrow() const { return n; }
               
            template <typename Target>
            inline void apply( Target& target ){
                auto it = target.begin() ; 
                auto source = sugar_begin(object) ;
                for( int j=0; j<n; j++, ++source ){
                    *it = *source ;
                    ++it ;
                    std::fill_n(it, it+n, 0 );
                }
            }
            
        private:
            const VEC_TYPE& object ;
            int n ;
        } ;
    
    } // sugar
    
    
    template <int RTYPE, bool NA, typename Vec>
    inline sugar::Diag_Maker<RTYPE, NA, Vec>
    diag( const VectorBase<RTYPE,NA,Vec>& x ){
        return sugar::Diag_Maker<RTYPE,NA,Vec>(x) ;    
    }
    
    template <int RTYPE, bool NA, typename Mat>
    inline sugar::Diag_Extractor<RTYPE, NA, Mat>
    diag( const MatrixBase<RTYPE, NA, Mat>& mat){
        return sugar::Diag_Extractor<RTYPE,NA,Mat>( mat ) ;    
    }

} // Rcpp
#endif

