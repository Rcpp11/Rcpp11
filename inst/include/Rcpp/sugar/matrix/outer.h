#ifndef Rcpp__sugar__outer_h
#define Rcpp__sugar__outer_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr1, typename Expr2, typename Function>
        class Outer : public SugarMatrixExpression<eT, Outer<eT, Expr1, Expr2, Function>> {
        public:
            typedef typename traits::vector_of<eT> Vec ;
            typedef typename std::result_of<Function(eT,eT)>::type value_type ;
            
            Outer( Vec lhs_, Vec rhs_, Function fun_ ) : 
                lhs(lhs_), rhs(rhs_), fun(fun_), nr(lhs.size()), nc(rhs.size()) {}
        
            inline eT operator()( int i, int j ) const {
                return fun( lhs[i], rhs[j] ) ;
            }
        
            inline R_xlen_t size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        
        private:
        
            Vec lhs, rhs ;
        
            Function fun ;
            int nr, nc ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr1, typename Expr2, typename Function>
    sugar::Outer<eT, Expr1, Expr2, Function>
    outer( const Rcpp::SugarVectorExpression<eT, Expr1>& lhs, const Rcpp::SugarVectorExpression<eT, Expr2>& rhs, Function fun ){
        return sugar::Outer<eT, Expr1, Expr2, Function>(lhs, rhs, fun ) ;
    }

} // Rcpp

#endif
