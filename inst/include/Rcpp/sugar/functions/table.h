#ifndef Rcpp__sugar__table_h
#define Rcpp__sugar__table_h
          
namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>        
        class Table {
        public:
            const static int RTYPE = traits::r_sexptype_traits<eT>::rtype ; 
            
            Table( const SugarVectorExpression<eT, Expr>& table ): map() {
                std::for_each( sugar_begin(table), sugar_end(table), [this](eT x){
                    map[x]++ ;            
                }) ;
            }
            
            inline IntegerVector get() const { 
                R_xlen_t n = map.size() ;
                IntegerVector result(n) ;
                CharacterVector names(n) ;
                R_xlen_t index=0 ;
                std::for_each( map.begin(), map.end(), [&]( const std::pair<eT,int>& p){
                    result[index] = p.second ;
                    names[index] = p.first ;
                    index++ ;
                }) ;
                result.names() = names ;
                return result ;
            }
            
        private:
            typedef std::map<eT, int> MAP ;
            MAP map ;
        }; 
        
    } // sugar
    
    template <typename eT, typename Expr>
    inline IntegerVector table( const SugarVectorExpression<eT, Expr>& x ){
        return sugar::Table<eT, Expr>(x).get() ;
    }


} // Rcpp
#endif

