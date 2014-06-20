#ifndef Rcpp__sugar__iterators_sugar_begin_h
#define Rcpp__sugar__iterators_sugar_begin_h

namespace Rcpp{
    namespace sugar {
        
        template <typename eT, typename Expr>
        inline typename Expr::const_iterator sugar_begin(const SugarVectorExpression<eT,Expr>& obj) {
            return obj.get_ref().begin() ;
        }
        
        template <typename eT, typename Expr>
        inline typename Expr::const_iterator sugar_end(const SugarVectorExpression<eT,Expr>& obj) {
            return obj.get_ref().end() ; ;
        }

    }
}

#endif
