#ifndef Rcpp__sugar__setdiff_h
#define Rcpp__sugar__setdiff_h
          
namespace Rcpp{
    namespace sugar{
           
        template <typename eT, typename Expr1, typename Expr2>
        class SetDiff : 
            public SugarVectorExpression<eT, SetDiff<eT, Expr1, Expr2>>, 
            public custom_sugar_vector_expression
        {
        public:
            typedef traits::vector_of<eT>::type Vector ;
            
            SetDiff( const SugarVectorExpression<eT,Expr1>& lhs, const SugarVectorExpression<eT,Expr2>& rhs) : 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {
                lhs_set.erase( rhs_set.begin(), rhs_set.end() ) ;
            }
            
            Vector get() const {
                return import( lhs_set.begin(), lhs_set.end() ) ;
            }
            
        private:
            typedef std::unordered_set<eT> SET ;
            SET lhs_set, rhs_set ;
            
        } ;
    
        template <typename eT, typename Expr1, typename Expr2>
        class SetEqual {
        public:
            SetEqual( const SugarVectorExpression<eT,Expr1>& lhs, const SugarVectorExpression<eT,Expr2>& rhs ) : 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {
                lhs_set.erase( rhs_set.begin(), rhs_set.end() ) ;
            }
            
            bool get() const {
                if( lhs_set.size() != rhs_set.size() ) return false ;
                
                return std::all_of( lhs_set.begin(), lhs_set.end(), [this](value_type x){
                        return rhs_set.count(x) ;
                }) ;
            }
            
        private:
            typedef std::unordered_set<eT> SET ;
            SET lhs_set, rhs_set ;
            
        } ;
        
        template <typename eT,typename Expr1, typename Expr2>
        class Intersect {
        public:
            typedef traits::vector_of<eT>::type Vector ;
            
            Intersect( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) :
                intersect(), 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {
                std::for_each( lhs_set.begin(), lhs_set.end(), [this]( value_type x){
                        if( rhs_set.count(x) ) intersect.insert(x) ;
                }) ;
            }
            
            Vector get() const {
                return import( intersect.begin(), intersect.end() ) ;
            }
            
        private:
            typedef std::unordered_set<eT> SET ;
            SET intersect, lhs_set, rhs_set ;
            
        } ;
        
        template <typename eT, typename Expr1, typename Expr2>
        class Union {
        public:
            typedef traits::vector_of<eT>::type Vector ;
            
            Union( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) : 
                result( sugar_begin(lhs), sugar_end(lhs) )
            {
                result.insert( sugar_begin(rhs), sugar_end(rhs) ) ;
            }
            
            Vector get() const {
                return import( result.begin(), result.end() ) ;
            }
            
        private:
            typedef std::unordered_set<eT> SET ;
            SET result ;
            
        } ;
        
        
    } // sugar
    
    template <typename eT, typename Expr1, typename Expr2>
    auto setdiff( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) -> decltype( sugar::SetDiff<eT, Expr1, Expr2>( lhs, rhs ).get() ) {
        return sugar::SetDiff<eT, Expr1, Expr2>( lhs, rhs ).get() ;
    }
    
    template <typename eT, typename Expr1, typename Expr2>
    bool setequal( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ){
        return sugar::SetEqual<eT, Expr1, Expr2>( lhs, rhs ).get() ;
    }
    
    template <typename eT, typename Expr1, typename Expr2>
    sugar::Intersect<eT, Expr1, Expr2> intersect( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ){
        return sugar::Intersect<eT, Expr1, Expr2>( lhs, rhs ) ;
    }
    
    // we cannot use "union" because it is a keyword
    template <typename eT, typename Expr1, typename Expr2>
    sugar::Union<eT, Expr1, Expr2> union_( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ){
        return sugar::Union<eT, Expr1, Expr2>( lhs, rhs ) ;
    }



} // Rcpp
#endif

