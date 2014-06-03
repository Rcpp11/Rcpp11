#ifndef Rcpp__sugar__tools_iterator_h
#define Rcpp__sugar__tools_iterator_h

namespace Rcpp {
namespace sugar { 

    /* generic sugar iterator type */
    template <typename eT, typename T>
    class SugarIterator {
    public:
        typedef eT value_type  ;
        typedef R_xlen_t difference_type  ;
        typedef value_type reference ;
        typedef const value_type const_reference ;
        typedef value_type* pointer ;
        typedef std::random_access_iterator_tag iterator_category ;
        typedef SugarIterator iterator ;
        
        SugarIterator( const T& ref_ ) : ref(ref_), index(0) {}
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
        inline reference operator[](R_xlen_t i){
            return ref[index+i] ;
        }
        inline const_reference operator[](R_xlen_t i) const {
            return ref[index+i] ;
        }
    
        inline reference operator*() {
            return ref[index] ;
        }
        inline const_reference operator*() const {
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
        R_xlen_t index ;
    } ;
    
    template <typename Expr, bool>
    struct sugar_iterator_type_dispatch ;
    
    template <typename Expr>
    struct sugar_iterator_type_dispatch<Expr,true>{
        typedef typename Expr::const_iterator type ;
    } ;
    
    template <typename Expr>
    struct sugar_iterator_type_dispatch<Expr,false>{
        typedef SugarIterator<Expr> type ;
    } ;
    
    template <typename T>
    struct sugar_iterator_type {
        typedef typename sugar_iterator_type_dispatch<T,traits::is_materialized<T>::type::value>::type type ;
    } ;
    
    
    template <typename eT, typename Expr>
    inline typename sugar_iterator_type<Expr>::type
    sugar_begin__impl(const SugarVectorExpression<eT, Expr>& obj, std::true_type ) {
        return obj.get_ref().begin() ;
    }
    
    template <typename eT, typename Expr>
    inline const SugarIterator<Expr> sugar_begin__impl(const SugarVectorExpression<eT,Expr>& obj, std::false_type ){
        return SugarIterator<eT,Expr>( obj.get_ref() ) ;
    }
    
    template <typename eT, typename Expr>
    inline auto sugar_begin(const SugarVectorExpression<eT,Expr>& obj) -> decltype( sugar_begin__impl( obj, typename traits::is_materialized<Expr>::type() ) ) {
        return sugar_begin__impl( obj, typename traits::is_materialized<Expr>::type() ) ;
    }
    
    template <typename eT, typename Expr>
    inline auto sugar_end(const SugarVectorExpression<eT,Expr>& obj) -> decltype( sugar_begin(obj) ){
        return sugar_begin<eT,Expr>(obj) + obj.size() ;
    }
    
    
}
}
#endif
