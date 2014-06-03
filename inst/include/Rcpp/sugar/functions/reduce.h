#ifndef Rcpp__sugar__functions__reduce_h
#define Rcpp__sugar__functions__reduce_h

namespace Rcpp {
    namespace sugar {

        template <typename eT, typename Expr, typename Callable>
        class Reduce {
        public:
            typedef typename std::result_of<Callable(eT,eT)>::type result_type ;
        
            Reduce( const SugarVectorExpression<eT,Expr>& expr_, Callable f_ ) : expr(expr_), f(f_) {
                if( expr.size() < 2 )
                    stop( "need at least two data points in reduce" ) ;
                auto it = sugar_begin(expr) ;
                auto init = *it ;
                ++it ;

                value = std::accumulate( it, sugar_end(expr), init, f )  ;
            }

            inline result_type get() const {
                return value ;
            }

        private:
            const SugarVectorExpression<eT,Expr>& expr ;
            Callable f ;
            result_type value ;

        } ;

    }

    template <typename eT, typename Expr, typename Callable>
    auto Reduce(Callable f, const SugarVectorExpression<RTYPE,Expr>& data) -> decltype( sugar::Reduce<eT,Expr,Callable>(data, f).get() ) {
        return sugar::Reduce<eT, Expr, Callable>(data, f).get() ;
    }


} // end namespace Rcpp


#endif
