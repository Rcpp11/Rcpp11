#ifndef Rcpp__sugar__row_h
#define Rcpp__sugar__row_h

namespace Rcpp{
    namespace sugar{
    
        class Row : 
            public SugarMatrixExpression<int,Row>, 
            public custom_sugar_matrix_expression
        {
        public:
            typedef int value_type ;
            Row( int nr_, int nc_) : nr(nr_), nc(nc_) {}
            
            inline int operator()( int i, int ) const {
                return i + 1 ;
            }
            
            inline R_xlen_t size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                for( int j=0; j<nc; j++, it += nr){
                    std::iota( it, it + nr, 1) ;
                }
            }
            
        private:
            int nr, nc ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Row row( const SugarMatrixExpression<eT, Expr>& lhs){
       return sugar::Row( lhs.nrow(), lhs.ncol() ) ;
    }

} // Rcpp

#endif
