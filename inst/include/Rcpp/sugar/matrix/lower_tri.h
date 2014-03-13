#ifndef Rcpp__sugar__lower_tri_h
#define Rcpp__sugar__lower_tri_h

namespace Rcpp{
    namespace sugar{
    
        class LowerTri : public MatrixBase<LGLSXP,false,LowerTri> {
        public:
            LowerTri( int nr_, int nc_, bool diag) : nr(nr_), nc(nc_), keep_diag(diag){}
            
            inline int operator()( int i, int j ) const {
               return keep_diag ? (i<=j) : (i<j) ;
            }
            
            inline int size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        	         
        private:
            int nr, nc ;
            bool keep_diag ;
        	
        } ;
    	
    } // sugar
    
    template <int RTYPE, bool LHS_NA, typename LHS_T>
    inline sugar::LowerTri lower_tri( const Rcpp::MatrixBase<RTYPE,LHS_NA,LHS_T>& lhs, bool diag = false){
        return sugar::LowerTri( lhs.nrow(), lhs.ncol(), diag ) ;
    }

} // Rcpp

#endif
