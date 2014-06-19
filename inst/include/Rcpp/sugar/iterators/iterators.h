#ifndef Rcpp__sugar__iterators_iterators_h
#define Rcpp__sugar__iterators_iterators_h

#include <Rcpp/sugar/iterators/transform_iterator.h>
#include <Rcpp/sugar/iterators/constant_iterator.h>
#include <Rcpp/sugar/iterators/indexing_iterator.h>
#include <Rcpp/sugar/iterators/each_iterator.h>

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
