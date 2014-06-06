#ifndef Rcpp__sugar__setdiff_h
#define Rcpp__sugar__setdiff_h
          
namespace Rcpp{
    namespace sugar{
           
        template <typename eT, typename Expr1, typename Expr2>
        class SetDiff : 
            public SugarVectorExpression<eT, SetDiff<eT, Expr1, Expr2>>
        {
        public:
            typedef std::unordered_set<eT> SET ;
            typedef typename SET::const_iterator const_iterator ;
            
            SetDiff( const SugarVectorExpression<eT,Expr1>& lhs, const SugarVectorExpression<eT,Expr2>& rhs) : 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {
                std::for_each( rhs_set.begin(), rhs_set.end(), [this](eT value){
                    lhs_set.erase(value) ;    
                }) ;
                
            }
            
            inline R_xlen_t size() const { return lhs_set.size(); }
            inline const_iterator begin() const { return lhs_set.begin() ; }
            inline const_iterator end() const { return lhs_set.end() ; }
            
        private:
            SET lhs_set, rhs_set ;
            
        } ;
    
        template <typename eT, typename Expr1, typename Expr2>
        class SetEqual {
        public:
            SetEqual( const SugarVectorExpression<eT,Expr1>& lhs, const SugarVectorExpression<eT,Expr2>& rhs ) : 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {}
            
            bool get() const {
                if( lhs_set.size() != rhs_set.size() ) return false ;
                
                return std::all_of( lhs_set.begin(), lhs_set.end(), [this](eT x){
                        return rhs_set.count(x) ;
                }) ;
            }
            
        private:
            typedef std::unordered_set<eT> SET ;
            SET lhs_set, rhs_set ;
            
        } ;
        
        template <typename eT,typename Expr1, typename Expr2>
        class Intersect : public SugarVectorExpression<eT, Intersect<eT, Expr1, Expr2>>{
        public:
            typedef std::unordered_set<eT> SET ;
            typedef typename SET::const_iterator const_iterator ;
            
            Intersect( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) :
                intersect(), 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {
                std::for_each( lhs_set.begin(), lhs_set.end(), [this]( eT x){
                        if( rhs_set.count(x) ) intersect.insert(x) ;
                }) ;
            }
            
            inline R_xlen_t size() const { return intersect.size(); }
            inline const_iterator begin() const { return intersect.begin() ; }
            inline const_iterator end() const { return intersect.end() ; }
            
        private:
            SET intersect, lhs_set, rhs_set ;
            
        } ;
        
        template <typename eT, typename Expr1, typename Expr2>
        class Union : public SugarVectorExpression<eT, Union<eT, Expr1, Expr2>>{
        public:
            typedef std::unordered_set<eT> SET ;
            typedef typename SET::const_iterator const_iterator ;
            
            Union( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) : 
                result( sugar_begin(lhs), sugar_end(lhs) )
            {
                result.insert( sugar_begin(rhs), sugar_end(rhs) ) ;
            }
            inline R_xlen_t size() const { return result.size(); }
            inline const_iterator begin() const { return result.begin() ; }
            inline const_iterator end() const { return result.end() ; }
            
        private:
            SET result ;
            
        } ;
        
        
    } // sugar
    
    template <typename eT, typename Expr1, typename Expr2>
    inline sugar::SetDiff<eT, Expr1, Expr2> setdiff( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) {
        return sugar::SetDiff<eT, Expr1, Expr2>( lhs, rhs );
    }
    
    template <typename eT, typename Expr1, typename Expr2>
    bool setequal( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ){
        return sugar::SetEqual<eT, Expr1, Expr2>( lhs, rhs ).get() ;
    }
    
    template <typename eT, typename Expr1, typename Expr2>
    sugar::Intersect<eT, Expr1, Expr2> intersect( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) {
        return sugar::Intersect<eT, Expr1, Expr2>( lhs, rhs ) ;
    }
    
    // we cannot use "union" because it is a keyword
    template <typename eT, typename Expr1, typename Expr2>
    sugar::Union<eT, Expr1, Expr2> union_( const SugarVectorExpression<eT, Expr1>& lhs, const SugarVectorExpression<eT, Expr2>& rhs ) {
        return sugar::Union<eT, Expr1, Expr2>( lhs, rhs ) ;
    }



} // Rcpp
#endif

