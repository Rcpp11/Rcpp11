#ifndef Rcpp__sugar__setdiff_h
#define Rcpp__sugar__setdiff_h
          
namespace Rcpp{
    namespace sugar{
           
        template <typename Expr1, typename Expr2>
        class SetDiff : 
            public SugarVectorExpression<SetDiff<Expr1, Expr2>>, 
            public custom_sugar_vector_expression
            {
        public:
            typedef typename Expr1::value_type value_type ;
            const static int RTYPE = traits::r_sexptype_traits<value_type>::rtype ; 
            
            SetDiff( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs) : 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {
                lhs_set.erase( rhs_set.begin(), rhs_set.end() ) ;
            }
            
            Vector<RTYPE> get() const {
                return import( lhs_set.begin(), lhs_set.end() ) ;
            }
            
        private:
            typedef std::unordered_set<value_type> SET ;
            SET lhs_set, rhs_set ;
            
        } ;
    
        template <typename Expr1, typename Expr2>
        class SetEqual {
        public:
            typedef typename Expr1::value_type value_type ;
            const static int RTYPE = traits::r_sexptype_traits<value_type>::rtype ; 
            
            SetEqual( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs ) : 
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
            typedef std::unordered_set<STORAGE> SET ;
            SET lhs_set, rhs_set ;
            
        } ;
        
        template <typename Expr1, typename Expr2>
        class Intersect {
        public:
            typedef typename Expr1::value_type value_type ;
            const static int RTYPE = traits::r_sexptype_traits<value_type>::rtype ; 
            
            Intersect( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs ) :
                intersect(), 
                lhs_set( sugar_begin(lhs), sugar_end(lhs) ), 
                rhs_set( sugar_begin(rhs), sugar_end(rhs) )
            {
                std::for_each( lhs_set.begin(), lhs_set.end(), [this]( value_type x){
                        if( rhs_set.count(x) ) intersect.insert(x) ;
                }) ;
            }
            
            Vector<RTYPE> get() const {
                return import( intersect.begin(), intersect.end() ) ;
            }
            
        private:
            typedef std::unordered_set<STORAGE> SET ;
            typedef typename SET::const_iterator ITERATOR ;
            SET intersect, lhs_set, rhs_set ;
            
        } ;
        
        template <typename Expr1, typename Expr2>
        class Union {
        public:
            typedef typename Expr1::value_type value_type ;
            const static int RTYPE = traits::r_sexptype_traits<value_type>::rtype ; 
            
            Union( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs ) : 
                result( sugar_begin(lhs), sugar_end(lhs) )
            {
                result.insert( sugar_begin(rhs), sugar_end(rhs) ) ;
            }
            
            Vector<RTYPE> get() const {
                return import( result.begin(), result.end() ) ;
            }
            
        private:
            typedef std::unordered_set<STORAGE> SET ;
            SET result ;
            
        } ;
        
        
    } // sugar
    
    template <typename Expr1, typename Expr2>
    inline typename std::enable_if<
        std::is_same< typename Expr1::value_type, typename Expr2::value_type>::value,
        sugar::SetDiff<Expr1, Expr2>
    >::type setdiff( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs ){
        return sugar::SetDiff<Expr1, Expr2>( lhs, rhs ) ;
    }
    
    template <typename Expr1, typename Expr2>
    inline typename std::enable_if<
        std::is_same< typename Expr1::value_type, typename Expr2::value_type>::value,
        bool
    >::type setequal( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs ){
        return sugar::SetEqual<Expr1, Expr2>( lhs, rhs ) ;
    }
    
    template <typename Expr1, typename Expr2>
    inline typename std::enable_if<
        std::is_same< typename Expr1::value_type, typename Expr2::value_type>::value,
        sugar::Intersect<Expr1, Expr2>
    >::type intersect( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs ){
        return sugar::Intersect<Expr1, Expr2>( lhs, rhs ) ;
    }
    
    // we cannot use "union" because it is a keyword
    template <typename Expr1, typename Expr2>
    inline typename std::enable_if<
        std::is_same< typename Expr1::value_type, typename Expr2::value_type>::value,
        sugar::Union<Expr1, Expr2>
    >::type union_( const SugarVectorExpression<Expr1>& lhs, const SugarVectorExpression<Expr2>& rhs ){
        return sugar::Union<Expr1, Expr2>( lhs, rhs ) ;
    }



} // Rcpp
#endif

