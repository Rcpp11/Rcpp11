#ifndef Rcpp__sugar__row_h
#define Rcpp__sugar__row_h

namespace Rcpp{
    namespace sugar{
    
        class Row : 
            public SugarMatrixExpression<INTSXP,false,Row>, 
            public custom_sugar_matrix_expression{
        public:
            Row( int nr_, int nc_) : nr(nr_), nc(nc_) {}
            
            inline int operator()( int i, int ) const {
                return i + 1 ;
            }
            
            inline R_xlen_t size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        
            template <typename Target>
            inline void apply( Target& target ){
                auto it = target.begin() ;
                for( int j=0; j<nc; j++, it += nr){
                    std::iota( it, it + nr, 1) ;
                }
            }
            
        private:
            int nr, nc ;
        } ;
    
    } // sugar
    
    template <int RTYPE, bool LHS_NA, typename LHS_T>
    inline sugar::Row row( const Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T>& lhs){
       return sugar::Row( lhs.nrow(), lhs.ncol() ) ;
    }

} // Rcpp

#endif
