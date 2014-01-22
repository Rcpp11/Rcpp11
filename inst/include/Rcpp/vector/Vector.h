#ifndef Rcpp__vector__Vector_h
#define Rcpp__vector__Vector_h

#include <Rcpp/vector/concat.h>

namespace Rcpp{
    
template <bool NA,typename T> class SingleLogicalResult ;

template <int RTYPE, template <class> class StoragePolicy>
class Vector :
    public StoragePolicy<Vector<RTYPE,StoragePolicy>>,     
    public SlotProxyPolicy<Vector<RTYPE,StoragePolicy>>,    
    public AttributeProxyPolicy<Vector<RTYPE,StoragePolicy>>,       
    public VectorBase< RTYPE, true, Vector<RTYPE,StoragePolicy> >, 
    public internal::eval_methods<RTYPE, StoragePolicy >, 
    public NamesProxyPolicy<Vector<RTYPE, StoragePolicy>>, 
    public AttributesProxyPolicy<Vector<RTYPE, StoragePolicy>>
{
public:
    typename traits::r_vector_cache_type<RTYPE>::type cache ;
    typedef typename traits::r_vector_proxy<RTYPE>::type Proxy ;
    typedef typename traits::r_vector_const_proxy<RTYPE>::type const_Proxy ;
    typedef typename traits::r_vector_name_proxy<RTYPE>::type NameProxy ;
    typedef typename traits::r_vector_const_name_proxy<RTYPE>::type const_NameProxy ;
    typedef typename traits::r_vector_proxy<RTYPE>::type value_type ;
    typedef typename traits::r_vector_iterator<RTYPE>::type iterator ;
    typedef typename traits::r_vector_const_iterator<RTYPE>::type const_iterator ;
    typedef typename traits::init_type<RTYPE>::type init_type ;
    typedef typename traits::r_vector_element_converter<RTYPE>::type converter_type ;
    typedef typename traits::storage_type<RTYPE>::type stored_type ;
	
    /** 
     * Default constructor. Creates a vector of the appropriate type
     * and 0 length
     */
    Vector() ;
    
    RCPP_GENERATE_CTOR_ASSIGN(Vector)
    
    // we can't define these 3 in meat for some reason
    // maybe because of the typedef in instantiation.h
    Vector( SEXP x ) {
        Storage::set__( r_cast<RTYPE>( x ) ) ;
    }
    Vector( const int& size, const stored_type& u ) {
        RCPP_DEBUG_CTOR(Vector, "( const int& size = %d, const stored_type& u )", size)
        Storage::set__( Rf_allocVector( RTYPE, size) ) ;
        fill( u ) ;
    }
    Vector( const int& size )  ;
    
    Vector( const Dimension& dims)  ;
    
    template <typename U> 
    Vector( const Dimension& dims, const U& u) ;
    
    template <typename U> 
    Vector( const int& size, const U& u) ;
    
    Vector( const std::string& st ) {
        RCPP_DEBUG_CTOR(Vector, "( const std::string& = %s )", st.c_str() )
        Storage::set__( internal::vector_from_string<RTYPE>(st) ) ;
    }
    Vector( const char* st ) {
        RCPP_DEBUG_CTOR(Vector, "( const char* = %s )", st )
        Storage::set__(internal::vector_from_string<RTYPE>(st));
    }
	
    template <bool NA, typename VEC> 
    Vector( const VectorBase<RTYPE,NA,VEC>& other )  ;
    
    template <bool NA, typename T> 
    Vector( const sugar::SingleLogicalResult<NA,T>& obj ) ;
         
    Vector( std::initializer_list<init_type> list ) {
        Storage::set__( r_cast<RTYPE>( wrap( list.begin(), list.end() ) ) );
    }

    template <typename T> Vector& 
    operator=( const T& x) ;
	
    static inline stored_type get_na() { return traits::get_na<RTYPE>(); }
    static inline bool is_na( stored_type x){ return traits::is_na<RTYPE>(x); }
    
    /**
     * the length of the vector, uses Rf_length
     */
    inline R_len_t length() const { return ::Rf_length( Storage::get__() ) ; }
    
    /**
     * alias of length
     */
    inline R_len_t size() const { return ::Rf_length( Storage::get__() ) ; }
    
    /**
     * one dimensional offset doing bounds checking to ensure
     * it is valid
     */
    size_t offset(const size_t& i) const {
        if( static_cast<R_len_t>(i) >= size() ) throw index_out_of_bounds() ;
        return i ;
    }
    
    R_len_t offset(const std::string& name) const {
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        if( names == R_NilValue ) throw index_out_of_bounds(); 
        int n = size() ;
        
        SEXP* data = internal::r_vector_start<STRSXP>(names) ;
        int index = std::find( data, data+n, Rf_mkChar(name.c_str()) ) - data ; 
        if( index == n ) throw index_out_of_bounds() ;
        return index ;
    }

    template <typename U>
    void fill( const U& u){
        fill__dispatch( typename traits::is_trivial<RTYPE>::type(), u ) ;
    }

    inline iterator begin() { return cache.get() ; }
    inline iterator end() { return cache.get() + size() ; }
    inline const_iterator begin() const{ return cache.get_const() ; }
    inline const_iterator end() const{ return cache.get_const() + size() ; }
	
    inline Proxy operator[]( int i ){ return cache.ref(i) ; }
    inline const_Proxy operator[]( int i ) const { return cache.ref(i) ; }
    
    inline Proxy at( int i ){ return cache.ref(i) ; }
    inline const_Proxy at( int i ) const { return cache.ref(i) ; }
    
    inline NameProxy operator[]( const std::string& name ){
        return NameProxy( *this, name ) ;
    }
    inline NameProxy at( const std::string& name ){
        return NameProxy( *this, name ) ;
    }
    inline NameProxy at( const std::string& name ) const {
        return NameProxy( *this, name ) ;
    }
    inline NameProxy operator[]( const std::string& name ) const {
        return NameProxy( const_cast<Vector&>(*this), name ) ;
    }
    
    Vector& sort(){
        std::sort( 
            internal::r_vector_start<RTYPE>(Storage::get__()), 
            internal::r_vector_start<RTYPE>(Storage::get__()) + size(), 
            typename traits::comparator_type<RTYPE>::type()
            ) ;
        return *this ;
    }

    template <typename T>
    void push_back( const T& object){
        push_back__impl( converter_type::get(object), 
                         typename std::is_same<stored_type,SEXP>()
                         ) ;
    }
	
    template <typename T>
    void push_back( const T& object, const std::string& name ){
        push_back_name__impl( converter_type::get(object), name, 
                              typename std::is_same<stored_type,SEXP>()
                              ) ;
    }
	
    template <typename T>
    void push_front( const T& object){
        push_front__impl( converter_type::get(object), 
                          typename std::is_same<stored_type,SEXP>() ) ;
    }
	
    template <typename T>
    void push_front( const T& object, const std::string& name){
        push_front_name__impl( converter_type::get(object), name, 
                               typename std::is_same<stored_type,SEXP>() ) ;
    }
	
public:
    
    template <typename T>
    iterator insert( iterator position, const T& object) ; 
    
    template <typename T>
    iterator insert( int position, const T& object){
        return insert( 
            cache.get() + position, 
            object
        ); 
    }
	
    iterator erase( int position){
        return erase_single__impl( cache.get() + position) ;
    }
	
    iterator erase( iterator position){
        return erase_single__impl( position ) ;
    }
	
    iterator erase( int first, int last){
        iterator start = cache.get() ;
        return erase_range__impl( start + first, start + last ) ;
    }
	
    iterator erase( iterator first, iterator last){
        return erase_range__impl( first, last ) ;
    }
	
    void update(SEXP /* x */){
        cache.update(*this) ;
    }
	
    template <typename EXPR_VEC>
    Vector& operator+=( const VectorBase<RTYPE,true,EXPR_VEC>& rhs ) ;
    
    template <typename EXPR_VEC>
    Vector& operator+=( const VectorBase<RTYPE,false,EXPR_VEC>& rhs ) ;
    
    /** 
     *  Does this vector have an element with the target name 
     */
    bool containsElementNamed( const char* target ) const ;
     

protected:
    
    // TODO: REMOVE
    inline int* dims() const {
        if( !::Rf_isMatrix(Storage::get__()) ) throw not_a_matrix() ;
        return INTEGER( ::Rf_getAttrib( Storage::get__(), R_DimSymbol ) ) ;
    }
    void init(){
        RCPP_DEBUG_CLASS(Vector, "::init( SEXP = <%p> )", Storage::get__() )
        internal::r_init_vector<RTYPE>(Storage::get__()) ;
    }

private:
    
    void push_back__impl(const stored_type& object, std::true_type ) ; 
    void push_back__impl(const stored_type& object, std::false_type ) ; 
	
    void push_back_name__impl(const stored_type& object, const std::string& name, std::true_type ) ;
    void push_back_name__impl(const stored_type& object, const std::string& name, std::false_type ) ;
	
    void push_front__impl(const stored_type& object, std::true_type ) ;
    void push_front__impl(const stored_type& object, std::false_type ) ;
	
    void push_front_name__impl(const stored_type& object, const std::string& name, std::true_type ) ; 
    void push_front_name__impl(const stored_type& object, const std::string& name, std::false_type ) ; 
		
    iterator erase_single__impl( iterator position ) ;
	
    iterator erase_range__impl( iterator first, iterator last ) ;

    template <bool NA, typename T> inline void assign_sugar_expression( const VectorBase<RTYPE,NA,T>& x ) ;
    
    // sugar
    template <typename T> inline void assign_object( const T& x, std::true_type )  ;
    
    // anything else
    template <typename T> inline void assign_object( const T& x, std::false_type ) ;
    	  
    // we are importing a real sugar expression, i.e. not a vector
    template <bool NA, typename VEC>
    inline void import_sugar_expression( const Rcpp::VectorBase<RTYPE,NA,VEC>& other, std::false_type ) ;
    
    // we are importing a sugar expression that actually is a vector
    template <bool NA, typename VEC>
    inline void import_sugar_expression( const Rcpp::VectorBase<RTYPE,NA,VEC>& other, std::true_type ) ;
    
    template <typename T>
    inline void import_expression( const T& other, int n ) ;
    
    template <typename U>
    void fill__dispatch( std::false_type, const U& u){
        // when this is not trivial, this is SEXP
        Shield<SEXP> elem = converter_type::get( u ); 
        iterator it(begin());
        for( int i=0; i<size() ; i++, ++it){
            *it = ::Rf_duplicate( elem ) ;
        }
    }
	
    template <typename U>
    void fill__dispatch( std::true_type, const U& u){
        std::fill( begin(), end(), converter_type::get( u ) ) ;
    }

public:
    template <typename... Args> static Vector create(Args... args) ;
    
    template <typename... Args> static Vector concat(Args... args){
        return concatenate<RTYPE,Args...>(args...) ;    
    }
    
} ; /* Vector */

}
#endif
