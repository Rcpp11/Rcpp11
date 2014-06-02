#ifndef Rcpp__sugar__diag_h
#define Rcpp__sugar__diag_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Diag_Extractor : public SugarVectorExpression<Diag_Extractor<Expr>> {
        public:
            typedef typename Expr::value_type value_type ;
            
            Diag_Extractor( const SugarMatrixExpression<Expr>& object_ ) : object(object_), n(0) {
                int nr = object.nrow() ;
                int nc = object.ncol() ;
                n = (nc < nr ) ? nc : nr ;
            }
        
            inline value_type operator[]( R_xlen_t i ) const {
                return object( i, i ) ;
            }
            inline R_xlen_t size() const { return n; }
        
        private:
            const SugarMatrixExpression<Expr>& object ;
            int n ;
        } ;
        
        
        template <typename Expr>
        class Diag_Maker : 
            public Rcpp::SugarMatrixExpression< Diag_Maker<Expr> >, 
            public custom_sugar_matrix_expression {
        public:
            typedef typename Expr::value_type value_type ;
        
            Diag_Maker( const SugarVectorExpression<Expr>& object_ ) : 
                object(object_), n(object_.size()) {}
        
            inline value_type operator()( int i, int j ) const {
                return (i==j) ? object[i] : 0 ;
            }
            inline R_xlen_t size() const { return n * n; }
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
            const SugarVectorExpression<Expr>& object ;
            int n ;
        } ;
    
    } // sugar
    
    
    template <typename Expr>
    inline sugar::Diag_Maker<Expr>
    diag( const SugarVectorExpression<Expr>& x ){
        return sugar::Diag_Maker<Expr>(x) ;    
    }
    
    template <typename Expr>
    inline sugar::Diag_Extractor<Expr>
    diag( const SugarMatrixExpression<Expr>& mat){
        return sugar::Diag_Extractor<Expr>(mat) ;    
    }

} // Rcpp
#endif

