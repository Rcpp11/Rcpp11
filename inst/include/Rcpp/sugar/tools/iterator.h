#ifndef Rcpp__sugar__tools_iterator_h
#define Rcpp__sugar__tools_iterator_h

namespace Rcpp {
namespace sugar { 

    /* generic sugar iterator type */
    template <typename T>
    class SugarIterator {
    public:
        typedef typename T::stored_type  stored_type  ;
        typedef stored_type value_type  ;
        typedef int difference_type  ;
        typedef stored_type reference ;
        typedef stored_type* pointer ;
        typedef std::random_access_iterator_tag iterator_category ;
        typedef SugarIterator iterator ;
        
        SugarIterator( const T& ref_ ) :ref(ref_), index(0) {}
        SugarIterator( const T& ref_, int index_) : ref(ref_), index(index_) {}
        SugarIterator( const SugarIterator& other) : ref(other.ref), index(other.index){}
        
        inline iterator& operator++(){ index++; return *this ; }
        inline iterator operator++(int){ 
            iterator orig(*this) ;
            ++(*this); 
            return orig ;
        }
        inline iterator& operator--(){ index--; return *this ; }
        inline iterator operator--(int){ 
            iterator orig(*this) ;
            --(*this); 
            return orig ;
        }
        inline iterator operator+(difference_type n) const {
            return iterator( ref, index+n ) ;
        }
        inline iterator operator-(difference_type n) const {
            return iterator( ref, index-n ) ;
        }
        inline iterator& operator+=(difference_type n) {
            index += n ;
            return *this ;
        }
        inline iterator& operator-=(difference_type n) {
            index -= n; 
            return *this ;
        }
        inline reference operator[](int i){
            return ref[index+i] ;
        }
    
        inline reference operator*() {
            return ref[index] ;
        }
        inline pointer operator->(){
            return &ref[index] ;
        }
    
        inline bool operator==( const iterator& y) const {
            return ( index == y.index ) ;
        }
        inline bool operator!=( const iterator& y) const {
            return ( index != y.index ) ;
        }
        inline bool operator<( const iterator& other ) const {
            return index < other.index ;
        }
        inline bool operator>( const iterator& other ) const {
            return index > other.index ;
        }
        inline bool operator<=( const iterator& other ) const {
            return index <= other.index ;        
        }
        inline bool operator>=( const iterator& other ) const {
            return index >= other.index ;
        }
                                                  
        inline difference_type operator-(const iterator& other) const {
            return index - other.index ;
        }

        
    private:   
        const T& ref ;
        int index ;
    } ;
    
    template <int RTYPE, bool NA, typename Expr>
    struct sugar_const_iterator_type {
        typedef SugarIterator<Expr> type;
    } ;
    
    template <int RTYPE, template <class> class StoragePolicy>
    struct sugar_const_iterator_type< RTYPE, true, Vector<RTYPE,StoragePolicy> > {
        typedef typename Vector<RTYPE,StoragePolicy>::const_iterator type;
    } ;
    
    template <int RTYPE, bool NA, typename Expr>
    inline typename sugar_const_iterator_type<RTYPE,NA,Expr>::type sugar_begin__impl(const VectorBase<RTYPE,NA,Expr>& obj, std::true_type ){
        return obj.get_ref().begin() ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    inline typename sugar_const_iterator_type<RTYPE,NA,Expr>::type sugar_begin__impl(const VectorBase<RTYPE,NA,Expr>& obj, std::false_type ){
        typedef typename sugar_const_iterator_type<RTYPE,NA,Expr>::type const_iterator ; 
        return const_iterator( obj.get_ref() ) ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    inline typename sugar_const_iterator_type<RTYPE,NA,Expr>::type sugar_begin(const VectorBase<RTYPE,NA,Expr>& obj){
        return sugar_begin__impl( obj, typename traits::is_materialized<Expr>::type() ) ;
    }
    
    template <int RTYPE, bool NA, typename Expr>
    inline typename sugar_const_iterator_type<RTYPE,NA,Expr>::type sugar_end(const VectorBase<RTYPE,NA,Expr>& obj){
        return sugar_begin<RTYPE,NA,Expr>(obj) + obj.size() ;
    }
    
    
}
}
#endif
