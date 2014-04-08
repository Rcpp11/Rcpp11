#ifndef Rcpp__sugar__col_h
#define Rcpp__sugar__col_h

namespace Rcpp{
    namespace sugar{
    
        class Col : public MatrixBase<INTSXP,false,Col> {
        public:
            Col( int nr_, int nc_) : nr(nr_), nc(nc_) {}
            
            inline int operator()( int , int j ) const {
                return j + 1 ;
            }
            
            inline int size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        
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
