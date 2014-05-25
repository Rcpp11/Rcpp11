#ifndef Rcpp__sugar__functions__filter_h
#define Rcpp__sugar__functions__filter_h

namespace Rcpp {
    namespace sugar {

        template <int RTYPE, typename Expr, typename Callable>
        class Filter : public SugarVectorExpression<RTYPE,true,Filter<RTYPE,Expr,Callable>> {
        public:
            typedef typename Rcpp::traits::storage_type<RTYPE>::type value_type ;

            Filter( const Expr& expr, Callable f_ ) : f(f_), data(){
                data.reserve(expr.size()) ;

                std::for_each( sugar_begin(expr), sugar_end(expr), [this]( value_type x){
                        if( f(x) ) data.push_back(x) ;
                }) ;

            }

            inline int size() const { return data.size(); }
            inline value_type operator[](int i) const { return data[i]; }

            template <typename Target>
            inline void apply( Target& target ) const {
                std::copy( data.begin(), data.end(), target.begin() ) ;
            }

        private:
            Callable f ;
            std::vector<value_type> data ;
        } ;

    }

    template <int RTYPE, bool NA, typename T, typename Callable>
    sugar::Filter<RTYPE, SugarVectorExpression<RTYPE, NA, T>, Callable>
    Filter(Callable f, const SugarVectorExpression<RTYPE, NA, T>& data){
        return sugar::Filter<RTYPE, SugarVectorExpression<RTYPE, NA, T>, Callable>( data, f ) ;
    }


} // end namespace Rcpp


#endif
