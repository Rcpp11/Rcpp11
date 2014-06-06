#ifndef Rcpp__sugar__col_h
#define Rcpp__sugar__col_h

namespace Rcpp{
    namespace sugar{
    
        class Col : 
            public SugarMatrixExpression<int,Col>, 
            public custom_sugar_matrix_expression {
        public:
            typedef int value_type ;
            
            Col( int nr_, int nc_) : nr(nr_), nc(nc_) {}
            
            inline int operator()( int , int j ) const {
                return j + 1 ;
            }
            
            inline R_xlen_t size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        
            template <typename Target>
            inline void apply( Target& target ){
                auto it = target.begin() ;
                for( int j=0; j<nc; j++){
                    std::fill_n( it, nr, j );
                    it += nr ;
                }
            }
            
        private:
            int nr, nc ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Col col( const SugarMatrixExpression<eT,Expr>& lhs){
       return sugar::Col( lhs.nrow(), lhs.ncol() ) ;
    }

} // Rcpp

#endif
