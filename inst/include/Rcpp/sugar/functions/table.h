#ifndef Rcpp__sugar__table_h
#define Rcpp__sugar__table_h
          
namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>        
        class Table {
        public:
            typedef typename Expr::value_type value_type ;
            const static int RTYPE = traits::r_sexptype_traits<value_type>::rtype ; 
            
            Table( const SugarVectorExpression<Expr>& table ): hash(), map() {
                std::for_each( sugar_begin(table), sugar_end(table), [this](value_type x){
                    map[x]++ ;            
                }) ;
            }
            
            inline IntegerVector get() const { 
                R_xlen_t n = map.size() ;
                IntegerVector result(n) ;
                CharacterVector names(n) ;
                R_xlen_t index=0 ;
                std::for_each( map.begin(), map.end(), [&]( const std::pair<value_type,int>& p){
                    result[index] = p.second ;
                    names[index] = p.first ;
                }) ;
                result.names() = names ;
                return result ;
            }
            
        private:
            typedef typename Rcpp::traits::comparator_type<RTYPE>::type Comp ;
            typedef std::map<STORAGE, int, Comp > MAP ;
            MAP map ;
        }; 
        
    } // sugar
    
    template <typename Expr>
    inline IntegerVector table( const SugarVectorExpression<Expr>& x ){
        return sugar::Table<Expr>(x).get() ;
    }


} // Rcpp
#endif

