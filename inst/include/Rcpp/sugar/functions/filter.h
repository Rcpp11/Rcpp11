#ifndef Rcpp__sugar__functions__filter_h
#define Rcpp__sugar__functions__filter_h

namespace Rcpp {
    namespace sugar {

        template <typename eT, typename Expr, typename Callable>
        class Filter : 
            public SugarVectorExpression<eT,Filter<eT,Expr,Callable>>, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename std::vector<eT>::const_iterator const_iterator ;
            
            Filter( const SugarVectorExpression<eT,Expr>& expr, Callable f_ ) : f(f_), data(){
                data.reserve(expr.size()) ;

                std::for_each( sugar_begin(expr), sugar_end(expr), [this]( eT x){
                        if( f(x) ) data.push_back(x) ;
                }) ;

            }

            inline R_xlen_t size() const { return data.size(); }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                std::copy( data.begin(), data.end(), target.begin() ) ;
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                apply(target) ;
            }
            
            template <typename Target>
            inline void apply_serial( Target& target ) const {
                apply(target) ;
            }
            
            inline const_iterator begin() const { return data.begin() ; }
            inline const_iterator end() const { return data.end() ; }
            
        private:
            Callable f ;
            std::vector<eT> data ;
        } ;

    }

    template <typename eT, typename Expr, typename Callable>
    sugar::Filter<eT, Expr, Callable>
    Filter(Callable f, const SugarVectorExpression<eT,Expr>& data){
        return sugar::Filter<eT, Expr, Callable>( data, f ) ;
    }

    
} // end namespace Rcpp


#endif
