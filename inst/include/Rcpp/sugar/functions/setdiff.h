#ifndef Rcpp__sugar__setdiff_h
#define Rcpp__sugar__setdiff_h
          
namespace Rcpp{
namespace sugar{
       
    template <typename SET>
    class RemoveFromSet {
    public:
        RemoveFromSet( SET& set_) : set(set_){}
        
        template <typename T>
        void operator()(T value){
            set.erase( value );    
        }
        
    private:
        SET& set ;
    } ;
    
    template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
    class SetDiff {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        SetDiff( const LHS_T& lhs, const RHS_T& rhs) : 
            lhs_set( get_begin(lhs), get_end(lhs) ), 
            rhs_set( get_begin(rhs), get_end(rhs) )
        {
            
            std::for_each( rhs_set.begin(), rhs_set.end(), RemoveFromSet<SET>(lhs_set) ) ;
        }
        
        Vector<RTYPE> get() const {
            int n = lhs_set.size() ;
            Vector<RTYPE> out = no_init(n) ;
            std::copy( lhs_set.begin(), lhs_set.end(), get_begin(out) ) ;
            return out ;
        }
        
    private:
        typedef std::unordered_set<STORAGE> SET ;
        typedef typename SET::const_iterator ITERATOR ;
        SET lhs_set ;
        SET rhs_set ;
        
    } ;

    template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
    class SetEqual {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        SetEqual( const LHS_T& lhs, const RHS_T& rhs) : 
            lhs_set( get_begin(lhs), get_end(lhs) ), 
            rhs_set( get_begin(rhs), get_end(rhs) )
        {
            
            std::for_each( rhs_set.begin(), rhs_set.end(), RemoveFromSet<SET>(lhs_set) ) ;
        }
        
        bool get() const {
            if( lhs_set.size() != rhs_set.size() ) return false ;
            
            ITERATOR it = lhs_set.begin(), end = lhs_set.end(), rhs_end = rhs_set.end() ;
            for( ; it != end; ){
                if( rhs_set.find(*it++) == rhs_end ) return false ;
            }
            return true ;
        }
        
    private:
        typedef std::unordered_set<STORAGE> SET ;
        typedef typename SET::const_iterator ITERATOR ;
        SET lhs_set ;
        SET rhs_set ;
        
    } ;
    
    template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
    class Intersect {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Intersect( const LHS_T& lhs, const RHS_T& rhs) : 
            intersect()
        {
            
            SET lhs_set( get_begin(lhs), get_end(lhs) ) ; 
            SET rhs_set( get_begin(rhs), get_end(rhs) ) ; 
            
            ITERATOR end = lhs_set.end() ;
            ITERATOR rhs_end = rhs_set.end() ;
            for( ITERATOR it=lhs_set.begin(); it != end; it++){
                if( rhs_set.find(*it) != rhs_end ) intersect.insert(*it) ;
            }
        }
        
        Vector<RTYPE> get() const {
            int n = intersect.size() ;
            Vector<RTYPE> out = no_init(n) ;
            std::copy( intersect.begin(), intersect.end(), get_begin(out) ) ;
            return out ;
        }
        
    private:
        typedef std::unordered_set<STORAGE> SET ;
        typedef typename SET::const_iterator ITERATOR ;
        SET intersect ;
        
    } ;
    
    template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
    class Union {
    public:
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Union( const LHS_T& lhs, const RHS_T& rhs) : 
            result( get_begin(lhs), get_end(lhs) )
        {
            result.insert( get_begin(rhs), get_end(rhs) ) ;
        }
        
        Vector<RTYPE> get() const {
            int n = result.size() ;
            Vector<RTYPE> out = no_init(n) ;
            std::copy( result.begin(), result.end(), get_begin(out) ) ;
            return out ;
        }
        
    private:
        typedef std::unordered_set<STORAGE> SET ;
        typedef typename SET::const_iterator ITERATOR ;
        SET result ;
        
    } ;
    
    
} // sugar

template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
inline Vector<RTYPE> setdiff( const VectorBase<RTYPE,LHS_NA,LHS_T>& lhs, const VectorBase<RTYPE,RHS_NA,RHS_T>& rhs ){
    return sugar::SetDiff<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T>( lhs.get_ref(), rhs.get_ref() ).get() ;
}

template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
inline bool setequal( const VectorBase<RTYPE,LHS_NA,LHS_T>& lhs, const VectorBase<RTYPE,RHS_NA,RHS_T>& rhs ){
    return sugar::SetEqual<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T>( lhs.get_ref(), rhs.get_ref() ).get() ;
}

template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
inline Vector<RTYPE> intersect( const VectorBase<RTYPE,LHS_NA,LHS_T>& lhs, const VectorBase<RTYPE,RHS_NA,RHS_T>& rhs ){
    return sugar::Intersect<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T>( lhs.get_ref(), rhs.get_ref() ).get() ;
}

// we cannot use "union" because it is a keyword
template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
inline Vector<RTYPE> union_( const VectorBase<RTYPE,LHS_NA,LHS_T>& lhs, const VectorBase<RTYPE,RHS_NA,RHS_T>& rhs ){
    return sugar::Union<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T>( lhs.get_ref(), rhs.get_ref() ).get() ;
}



} // Rcpp
#endif

