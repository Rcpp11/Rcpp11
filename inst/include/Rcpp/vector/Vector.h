// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013 Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Rcpp__vector__Vector_h
#define Rcpp__vector__Vector_h

namespace Rcpp{
    
template <bool NA,typename T> class SingleLogicalResult ;

template <int RTYPE, template <class> class StoragePolicy>
class Vector_Impl :
    public StoragePolicy<Vector_Impl<RTYPE,StoragePolicy>>,     
    public SlotProxyPolicy<Vector_Impl<RTYPE,StoragePolicy>>,    
    public AttributeProxyPolicy<Vector_Impl<RTYPE,StoragePolicy>>,       
    public VectorBase< RTYPE, true, Vector_Impl<RTYPE,StoragePolicy> >, 
    public internal::eval_methods<RTYPE> 
{
    typename traits::r_vector_cache_type<RTYPE>::type cache ;
    
    using Storage = RObjectStorage<Vector_Impl> ;
    using AttributeProxy_ = AttributeProxyPolicy<Vector_Impl> ;
    
public:
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
    Vector_Impl() ;
    
    Vector_Impl( const Vector_Impl& other ){        
        Storage::copy__(other) ;                         
    }                                           
    Vector_Impl( Vector_Impl&& other ){             
        Storage::steal__(other) ;                        
    }                                           
    Vector_Impl& operator=( Vector_Impl&& other ){  
        return Storage::steal__( other );                
    }                                           
    Vector_Impl& operator=(const Vector_Impl& rhs) {
        return Storage::copy__(rhs) ;                    
    }                                           
    
    // we can't define these 3 in meat for some reason
    // maybe because of the typedef in instantiation.h
    Vector_Impl( SEXP x ) {
        Storage::set__( r_cast<RTYPE>( x ) ) ;
    }
    Vector_Impl( const int& size, const stored_type& u ) {
        RCPP_DEBUG_CTOR(Vector_Impl, "( const int& size = %d, const stored_type& u )", size)
        Storage::set__( Rf_allocVector( RTYPE, size) ) ;
        fill( u ) ;
    }
    Vector_Impl( const int& size )  ;
    
    Vector_Impl( const Dimension& dims)  ;
    
    template <typename U> 
    Vector_Impl( const Dimension& dims, const U& u) ;
    
    template <typename U> 
    Vector_Impl( const int& size, const U& u) ;
    
    Vector_Impl( const std::string& st ) {
        RCPP_DEBUG_CTOR(Vector, "( const std::string& = %s )", st.c_str() )
        Storage::set__( internal::vector_from_string<RTYPE>(st) ) ;
    }
    Vector_Impl( const char* st ) {
        RCPP_DEBUG_CTOR(Vector, "( const char* = %s )", st )
        Storage::set__(internal::vector_from_string<RTYPE>(st));
    }
	
    template <bool NA, typename VEC> 
    Vector_Impl( const VectorBase<RTYPE,NA,VEC>& other )  ;
    
    template <bool NA, typename T> 
    Vector_Impl( const sugar::SingleLogicalResult<NA,T>& obj ) ;
         
    Vector_Impl( std::initializer_list<init_type> list ) {
        Storage::set__( r_cast<RTYPE>( wrap( list.begin(), list.end() ) ) );
    }

	template <typename T> Vector_Impl& 
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
        R_len_t n=size() ;
        for( R_len_t i=0; i<n; ++i){
            if( ! name.compare( CHAR(STRING_ELT(names, i)) ) ){
                return i ;
            }
        }
        throw index_out_of_bounds() ;
        return -1 ; /* -Wall */
    }

    template <typename U>
    void fill( const U& u){
        fill__dispatch( typename traits::is_trivial<RTYPE>::type(), u ) ;
    }

    class NamesProxy {
    public:
        NamesProxy( Vector_Impl& v) : parent(v){} ;
	
        /* lvalue uses */              
        NamesProxy& operator=(const NamesProxy& rhs) {
            set( rhs.get() ) ;
            return *this ;
        }
	
        template <typename T>
        NamesProxy& operator=(const T& rhs){
            set( wrap(rhs) ) ;
            return *this ;
        }
	
        template <typename T> operator T() const {
            return Rcpp::as<T>(get()) ;
        }
		
    private:
        Vector_Impl& parent; 
		
        SEXP get() const {
            return RCPP_GET_NAMES(parent) ;
        }
		
        void set(SEXP x) const {
			
            /* check if we can use a fast version */         
            if( TYPEOF(x) == STRSXP && parent.size() == Rf_length(x) ){
                SEXP y = parent.get__() ; 
                Rf_setAttrib( y, R_NamesSymbol, x ) ;
            } else {
                /* use the slower and more flexible version (callback to R) */
                SEXP namesSym = Rf_install( "names<-" );
                Scoped<SEXP> new_vec = internal::try_catch(Rf_lang3( namesSym, parent, x )) ;
                /* names<- makes a new vector, so we have to change 
                   the SEXP of the parent of this proxy */
                parent.set__( new_vec ) ;
            }
    		
        }
    		
    } ;
    	
    class const_NamesProxy {
    public:
        const_NamesProxy( const Vector_Impl& v) : parent(v){} ;
	
        /* lvalue uses */              
        NamesProxy& operator=(const NamesProxy& rhs) = delete ;
	
        template <typename T> operator T() const {
            return Rcpp::as<T>(get()) ;
        }
		
    private:
        const Vector_Impl& parent; 
		
        SEXP get() const {
            return RCPP_GET_NAMES(parent) ;
        }
		
    } ;
    	
    
    NamesProxy names() {
        return NamesProxy(*this) ;
    }
    const_NamesProxy names() const {
        return NamesProxy(*this) ;
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
        return NameProxy( const_cast<Vector_Impl&>(*this), name ) ;
    }
    
    Vector_Impl& sort(){
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
	
    void update(SEXP x){
        cache.update(*this) ;
    }
	
    typedef internal::RangeIndexer<RTYPE,true,Vector_Impl> Indexer ;
	
    inline Indexer operator[]( const Range& range ){
        return Indexer( const_cast<Vector_Impl&>(*this), range );
    }
    
    template <typename EXPR_VEC>
    Vector_Impl& operator+=( const VectorBase<RTYPE,true,EXPR_VEC>& rhs ) ;
    
    template <typename EXPR_VEC>
    Vector_Impl& operator+=( const VectorBase<RTYPE,false,EXPR_VEC>& rhs ) ;
    
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
        RCPP_DEBUG_CLASS(Vector_Impl, "::init( SEXP = <%p> )", Storage::get__() )
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
        Scoped<SEXP> elem = converter_type::get( u ); 
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
    template <typename... Args> static Vector_Impl create(Args... args) ;
    
} ; /* Vector */

}
#endif
