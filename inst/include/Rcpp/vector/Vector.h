//
// Vector.h:  vectors
//
// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
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

// forward declarations
class Dimension ;

template <bool NA,typename T> class SingleLogicalResult ;

template <int RTYPE>
class Vector :
    public RObject,       
    public VectorBase< RTYPE, true, Vector<RTYPE> >, 
    public internal::eval_methods<RTYPE> 
{
    typename traits::r_vector_cache_type<RTYPE>::type cache ;
    
public:
    typedef typename traits::r_vector_proxy<RTYPE>::type Proxy ;
    typedef typename traits::r_vector_const_proxy<RTYPE>::type const_Proxy ;
    typedef typename traits::r_vector_name_proxy<RTYPE>::type NameProxy ;
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
    
    /**
     * Destructor. Prints some information id debugging is enabled
     */
    ~Vector() ;
    
    /**
     * copy constructor. shallow copy of the SEXP
     */
    Vector( const Vector& other) ;
	
    Vector( Vector&& other) ;
    Vector& operator=( Vector&& other );
    
    // we can't define these 3 in meat for some reason
    // maybe because of the typedef in instantiation.h
    Vector( SEXP x ) : RObject( r_cast<RTYPE>( x ) ) {
        RCPP_DEBUG_CTOR(Vector, "(SEXP = <%p>)", x )
        update_vector() ;
    }
    Vector( const int& size, const stored_type& u ) : RObject( Rf_allocVector( RTYPE, size) ) {
        RCPP_DEBUG_CTOR(Vector, "( const int& size = %d, const stored_type& u )", size)
        update_vector() ;
        fill( u ) ;
    }
    Vector( const int& size )  ;
    
    Vector( const Dimension& dims)  ;
    
    template <typename U> 
    Vector( const Dimension& dims, const U& u) ;
    
    template <typename U> 
    Vector( const int& size, const U& u) ;
    
    Vector( const std::string& st ) : RObject( internal::vector_from_string<RTYPE>(st) ){
        RCPP_DEBUG_CTOR(Vector, "( const std::string& = %s )", st.c_str() )
        update_vector();
    }
    Vector( const char* st ) : RObject( internal::vector_from_string<RTYPE>(st) ){
        RCPP_DEBUG_CTOR(Vector, "( const char* = %s )", st )
        update_vector();
    }
	
    template <bool NA, typename VEC> 
    Vector( const VectorBase<RTYPE,NA,VEC>& other )  ;
    
    template <bool NA, typename T> 
    Vector( const sugar::SingleLogicalResult<NA,T>& obj ) ;
         
    Vector( std::initializer_list<init_type> list ) : RObject(){
        assign( list.begin() , list.end() ) ;
    }
    Vector( std::initializer_list<typename traits::named_object<init_type>> list ) : 
        Vector(wrap(list.begin(), list.end())){}

	/**
     * Assignment operator. Grab the SEXP of the other vector
     */
    Vector& operator=( const Vector& other ) ;
	
    template <typename T> Vector& 
    operator=( const T& x) ;
	
    static inline stored_type get_na() { return traits::get_na<RTYPE>(); }
    static inline bool is_na( stored_type x){ return traits::is_na<RTYPE>(x); }
    
    /**
     * the length of the vector, uses Rf_length
     */
    inline R_len_t length() const { return ::Rf_length( RObject::m_sexp ) ; }
    
    /**
     * alias of length
     */
    inline R_len_t size() const { return ::Rf_length( RObject::m_sexp ) ; }
    
    /**
     * offset based on the dimensions of this vector
     */
    size_t offset(const size_t& i, const size_t& j) const {
        if( !::Rf_isMatrix(RObject::m_sexp) ) throw not_a_matrix() ;
        /* we need to extract the dimensions */
        int *dim = dims() ;
        size_t nrow = static_cast<size_t>(dim[0]) ;
        size_t ncol = static_cast<size_t>(dim[1]) ;
        if( i >= nrow || j >= ncol ) throw index_out_of_bounds() ;
        return i + nrow*j ;
    }
    
    /**
     * one dimensional offset doing bounds checking to ensure
     * it is valid
     */
    size_t offset(const size_t& i) const {
        if( static_cast<R_len_t>(i) >= ::Rf_length(RObject::m_sexp) ) throw index_out_of_bounds() ;
        return i ;
    }
    
    R_len_t offset(const std::string& name) const {
        SEXP names = RCPP_GET_NAMES( RObject::m_sexp ) ;
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
        NamesProxy( Vector& v) : parent(v){} ;
	
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
        Vector& parent; 
		
        SEXP get() const {
            return RCPP_GET_NAMES(parent) ;
        }
		
        void set(SEXP x) const {
			
            /* check if we can use a fast version */         
            if( TYPEOF(x) == STRSXP && parent.size() == Rf_length(x) ){
                SEXP y = parent.asSexp() ; 
                Rf_setAttrib( y, R_NamesSymbol, x ) ;
            } else {
                /* use the slower and more flexible version (callback to R) */
                SEXP namesSym = Rf_install( "names<-" );
                SEXP new_vec = PROTECT( internal::try_catch(Rf_lang3( namesSym, parent, x ))) ;
                /* names<- makes a new vector, so we have to change 
                   the SEXP of the parent of this proxy */
                parent.set_sexp( new_vec ) ;
                UNPROTECT(1) ; /* new_vec */
            }
    		
        }
    		
    } ;
    	
    class const_NamesProxy {
    public:
        const_NamesProxy( const Vector& v) : parent(v){} ;
	
        /* lvalue uses */              
        NamesProxy& operator=(const NamesProxy& rhs) = delete ;
	
        template <typename T> operator T() const {
            return Rcpp::as<T>(get()) ;
        }
		
    private:
        const Vector& parent; 
		
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
    
    inline Proxy operator()( const size_t& i) {
        return cache.ref( offset(i) ) ;
    }
    inline const_Proxy operator()( const size_t& i) const {
        return cache.ref( offset(i) ) ;
    }
    
    inline Proxy operator()( const size_t& i, const size_t& j) {
        return cache.ref( offset(i,j) ) ;
    }
    inline const_Proxy operator()( const size_t& i, const size_t& j) const {
        return cache.ref( offset(i,j) ) ;
    }
	
    inline NameProxy operator[]( const std::string& name ){
        return NameProxy( *this, name ) ;
    }
    inline NameProxy operator()( const std::string& name ){
        return NameProxy( *this, name ) ;
    }
	
    inline NameProxy operator[]( const std::string& name ) const {
        return NameProxy( const_cast<Vector&>(*this), name ) ;
    }
    inline NameProxy operator()( const std::string& name ) const {
        return NameProxy( const_cast<Vector&>(*this), name ) ;
    }
	
    Vector& sort(){
        std::sort( 
            internal::r_vector_start<RTYPE>(m_sexp), 
            internal::r_vector_start<RTYPE>(m_sexp) + size(), 
            typename traits::comparator_type<RTYPE>::type()
            ) ;
        return *this ;
    }

    template <typename InputIterator>
    void assign( InputIterator first, InputIterator last){
        /* FIXME: we can do better than this r_cast to avoid 
           allocating an unnecessary temporary object
        */
        SEXP x = PROTECT( r_cast<RTYPE>( wrap( first, last ) ) );
        RObject::setSEXP( x) ;
        update_vector() ;
        UNPROTECT(1) ;
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
	
    void update_vector(){
        RCPP_DEBUG_CLASS(Vector, "::update_vector( SEXP = < %p > )", reinterpret_cast<void*>( RObject::asSexp() ) )
        cache.update(*this) ;
    }
	
    void set_sexp(SEXP x){
        RObject::setSEXP( x) ;
        update_vector() ;
    }
    typedef internal::RangeIndexer<RTYPE,true,Vector> Indexer ;
	
    inline Indexer operator[]( const Range& range ){
        return Indexer( const_cast<Vector&>(*this), range );
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
    inline int* dims() const {
        if( !::Rf_isMatrix(RObject::m_sexp) ) throw not_a_matrix() ;
        return INTEGER( ::Rf_getAttrib( RObject::m_sexp, R_DimSymbol ) ) ;
    }
    void init(){
        RCPP_DEBUG_CLASS(Vector, "::init( SEXP = <%p> )", RObject::m_sexp )
        internal::r_init_vector<RTYPE>(RObject::m_sexp) ;
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
        SEXP elem = PROTECT( converter_type::get( u ) ); 
        iterator it(begin());
        for( int i=0; i<size() ; i++, ++it){
            *it = ::Rf_duplicate( elem ) ;
        }
        UNPROTECT(1) ; /* elem */
    }
	
    template <typename U>
    void fill__dispatch( std::true_type, const U& u){
        std::fill( begin(), end(), converter_type::get( u ) ) ;
    }

public:
    
    static Vector create(){
        return Vector( 0 ) ;
    }
    template <typename... Args> static Vector create(Args... args) ;
    
private:
    
    template <typename T, typename... Args>
    void set_value( traits::number_to_type<sizeof...(Args) + 1>, int i, const T& obj, const Args&... pack ) ;
    
    template <typename T>
    void set_value( traits::number_to_type<1>, int i, const T& obj ) ;
    
    template <typename T, typename... Args>
    void set_value_with_names( traits::number_to_type<sizeof...(Args) + 1>, int i, SEXP names, const T& obj, const Args&... pack ) ;
    
    template <typename T>
    void set_value_with_names( traits::number_to_type<1>, int i, SEXP names, const T& obj ) ;
    
    template <typename... Args> static Vector create__impl(std::true_type  , Args... );
    template <typename... Args> static Vector create__impl(std::false_type , Args... );
    
    
} ; /* Vector */

#endif
