#ifndef Rcpp__sugar__col_h
#define Rcpp__sugar__col_h

namespace Rcpp{
    namespace sugar{
    
        class Col : 
            public SugarMatrixExpression<INTSXP,false,Col>, 
            public custom_sugar_matrix_expression {
        public:
            Col( int nr_, int nc_) : nr(nr_), nc(nc_) {}
            
            inline int operator()( int , int j ) const {
                return j + 1 ;
            }
            
            inline int size() const { return nr * nc ; }
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
    
    template <int RTYPE, bool LHS_NA, typename LHS_T>
    inline sugar::Col col( const Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T>& lhs){
       return sugar::Col( lhs.nrow(), lhs.ncol() ) ;
    }

} // Rcpp

#endif
