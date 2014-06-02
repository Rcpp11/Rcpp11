#ifndef Rcpp__sugar__functions__filter_h
#define Rcpp__sugar__functions__filter_h

namespace Rcpp {
    namespace sugar {

        template <typename Expr, typename Callable>
        class Filter : 
            public SugarVectorExpression<Filter<Expr,Callable>>, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename Expr::value_type value_type ;
            typedef std::vector<value_type>::const_iterator const_iterator ;
            
            Filter( const Expr& expr, Callable f_ ) : f(f_), data(){
                data.reserve(expr.size()) ;

                std::for_each( sugar_begin(expr), sugar_end(expr), [this]( value_type x){
                        if( f(x) ) data.push_back(x) ;
                }) ;

            }

            inline R_xlen_t size() const { return data.size(); }
            inline value_type operator[](R_xlen_t i) const { return data[i]; }

            template <typename Target>
            inline void apply( Target& target ) const {
                std::copy( data.begin(), data.end(), target.begin() ) ;
            }
            
            inline const_iterator begin() const {
                return data.begin();
            }
            inline const_iterator end() const {
                return data.end();
            }

        private:
            Callable f ;
            std::vector<value_type> data ;
        } ;

    }

    template <typename Expr, typename Callable>
    sugar::Filter<Expr, Callable>
    Filter(Callable f, const SugarVectorExpression<Expr>& data){
        return sugar::Filter<Expr, Callable>( data, f ) ;
    }


} // end namespace Rcpp


#endif
