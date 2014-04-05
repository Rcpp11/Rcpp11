#ifndef Rcpp__vector__VectorBase_h
#define Rcpp__vector__VectorBase_h

namespace Rcpp{
	
/** a base class for vectors, modelled after the CRTP */
template <int RTYPE, bool na, typename VECTOR>
class VectorBase : public traits::VectorExpression {
public:
    struct r_type : std::integral_constant<int,RTYPE>{} ;
    typedef typename traits::storage_type<RTYPE>::type stored_type ;
    typedef typename traits::storage_type<RTYPE>::type elem_type ;
	
	VECTOR& get_ref(){
		return static_cast<VECTOR&>(*this) ;
	}
	
	const VECTOR& get_ref() const {
		return static_cast<const VECTOR&>(*this) ;
	}

	inline stored_type operator[]( int i) const {
	    return get_ref()[i] ;
	}
	
	inline int size() const { 
	    return get_ref().size() ;
	}
	
	class iterator {
	public:
		typedef stored_type reference ;
		typedef stored_type* pointer ;
		typedef int difference_type ;
		typedef stored_type value_type;
		typedef std::random_access_iterator_tag iterator_category ;

		iterator( const VectorBase& object_, int index_ ) : object(object_.get_ref()), index(index_){} 
		iterator( const iterator& other) : object(other.object), index(other.index){}
		
		inline iterator& operator++(){
			index++ ;
			return *this ;
		}
		inline iterator operator++(int){
			iterator orig(*this); 
		    ++(*this) ;
			return orig ;
		}
		
		inline iterator& operator--(){
			index-- ;
			return *this ;
		}
		inline iterator operator--(int){
			iterator orig(*this); 
		    --(*this) ;
			return orig ;
		}
		                    
		inline iterator operator+(difference_type n) const {
			return iterator( object, index+n ) ;
		}
		inline iterator operator-(difference_type n) const {
			return iterator( object, index-n ) ;
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
		    return object[index+i] ;
		}
		
		inline reference operator*() {
			return object[index] ;
		}
		inline pointer operator->(){
			return &object[index] ;
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
		const VECTOR& object ;
		int index; 
	} ;
	
	inline iterator begin() const { return iterator(*this, 0) ; }
	inline iterator end() const { return iterator(*this, size() ) ; }
	
} ;

} // namespace Rcpp
#endif
