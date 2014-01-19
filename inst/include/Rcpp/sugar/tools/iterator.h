#ifndef Rcpp__sugar__tools_iterator_h
#define Rcpp__sugar__tools_iterator_h

namespace Rcpp {
namespace sugar { 

    /* generic sugar iterator type */
    template <typename T>
    class SugarIterator {
    public:
        
        typedef int difference_type ;
        typedef typename Rcpp::traits::storage_type< Rcpp::traits::r_sexptype_traits<T>::rtype >::type STORAGE_TYPE ;
        typedef STORAGE_TYPE reference ;
        typedef STORAGE_TYPE* pointer ;
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
    
    template <typename T> struct sugar_const_iterator_type {
        typedef SugarIterator<T> type ;
    } ;
    template <int RTYPE> struct sugar_const_iterator_type< Rcpp::Vector<RTYPE> >{
        typedef typename Rcpp::Vector<RTYPE>::const_iterator type ;
    } ;
    template <> struct sugar_const_iterator_type< CharacterVector >{
        typedef SEXP* type ;
    } ;
    
    
    template <typename T> struct is_sugar_vector : public std::false_type{} ;
    template <int RTYPE> struct is_sugar_vector< Rcpp::Vector<RTYPE> > : public std::true_type{} ;
    
    
    template <typename T>
    inline typename sugar_const_iterator_type<T>::type get_begin__impl(const T& obj, std::true_type ){
        return obj.begin() ;
    }
    template <typename T>
    inline typename sugar_const_iterator_type<T>::type get_begin__impl(const T& obj, std::false_type ){
        typedef typename sugar_const_iterator_type<T>::type const_iterator ; 
        return const_iterator( obj ) ;
    }
    
    
    
    template <typename T>
    inline typename sugar_const_iterator_type<T>::type get_begin(const T& obj){
        return get_begin__impl( obj, typename is_sugar_vector<T>::type() ) ;
    }
    /* full specialization for character vectors */
    template <>
    inline SEXP* get_begin(const CharacterVector& obj){
        return get_string_ptr(obj) ;
    }
    
    template <typename T>
    inline typename sugar_const_iterator_type<T>::type get_end(const T& obj){
        return get_begin<T>(obj) + obj.size() ;
    }
    
    
}
}
#endif
