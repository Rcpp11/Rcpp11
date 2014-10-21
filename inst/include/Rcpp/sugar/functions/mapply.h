#ifndef Rcpp__sugar__mapply_h
#define Rcpp__sugar__mapply_h

namespace Rcpp{
    namespace sugar{

        template <typename input_type, bool>
        struct mapply_iterator_dispatch ;
        
        template <typename input_type>
        struct mapply_iterator_dispatch<input_type, true> {
            typedef constant_iterator<typename std::decay<input_type>::type > type ;
        } ;
        
        template <typename input_type>
        struct mapply_iterator_dispatch<input_type, false> {
            typedef typename input_type::expr_type::const_iterator type ;
        } ;
        
        template <typename input_type>
        struct mapply_iterator {
            typedef typename mapply_iterator_dispatch< 
                typename std::decay<input_type>::type, 
                Rcpp::traits::is_primitive<input_type>::value 
            >::type type ;
        } ;
        
        template <typename Tup, int... S>
        bool any_na( const Tup& tup, Rcpp::traits::sequence<S...> ){
            std::initializer_list<bool> tests = { (std::get<S>(tup) == NA)... } ;
            bool res = std::any_of( tests.begin(), tests.end(), [](bool b){ return b; } ) ;
            return res ;
        }
        
        template <
            typename Function,
            typename... Args
        >
        class Mapply :
            public SugarVectorExpression<
                typename std::result_of<Function(typename traits::mapply_scalar_type<Args>::type ...)>::type, 
                Mapply<Function,Args...>
            >, 
            public custom_sugar_vector_expression
        {
        public:
            const static int N = sizeof...(Args);
            typedef typename Rcpp::traits::index_sequence<Args...>::type Sequence ;
            typedef std::tuple< typename std::conditional<traits::is_primitive<Args>::value, typename std::decay<Args>::type, Args>::type ...> Tuple ;
            typedef std::tuple< typename traits::mapply_scalar_type<Args>::type ... > ETuple ;
            typedef typename std::result_of<Function(typename traits::mapply_scalar_type<Args>::type ...)>::type real_value_type ;
            typedef typename std::conditional< std::is_same<bool,real_value_type>::value, Rboolean, real_value_type>::type value_type ;
            typedef std::tuple< typename mapply_iterator<Args>::type ... > IteratorsTuple ;
            typedef typename Rcpp::traits::index_sequence_that<Rcpp::traits::is_primitive, Args...>::type prim_sequence ;
            typedef typename Rcpp::traits::index_sequence_that<Rcpp::traits::is_not_primitive, Args...>::type not_prim_sequence ;
            
        // private:
            Tuple data ;
            Function fun ;
            R_xlen_t n ;
            bool any_prim_na ;

        public:
                 
            class MapplyIterator {
            public:
                typedef std::bidirectional_iterator_tag iterator_category ;
                typedef int difference_type ;
                typedef typename Mapply::value_type value_type ;
                typedef value_type reference ;
                typedef value_type* pointer ;
                
                MapplyIterator( const Tuple& data, Function fun_, bool any_prim_na_, int pos = 0 ) : 
                    iterators( get_iterators(data, pos, Sequence() ) ), fun(fun_), index(pos), any_prim_na(any_prim_na_)
                {}
                
                MapplyIterator( const MapplyIterator& other ) : 
                    iterators(other.iterators), fun(other.fun), index(other.index), any_prim_na(other.any_prim_na){}
                
                inline MapplyIterator& operator++(){
                    increment_all( Sequence() ) ;
                    ++index ;
                    return *this ;
                }
                
                inline MapplyIterator& operator--(){
                    decrement_all( Sequence() ) ;
                    --index ;
                    return *this ;
                }
                
                inline MapplyIterator& operator+=(int n){
                    increment_all( n, Sequence() ) ;
                    index += n ;
                    return *this ;
                }
                
                inline MapplyIterator& operator-=(int n){
                    decrement_all( n, Sequence() ) ;
                    index -= n ;
                    return *this ;
                }
                
                MapplyIterator operator+( int n){
                    MapplyIterator copy(*this) ;
                    copy += n;
                    return copy ;
                }
                
                MapplyIterator operator-( int n) const {
                    MapplyIterator copy(*this) ;
                    copy -= n;
                    return copy ;
                }
                
                int operator-( const MapplyIterator& other) const {
                    return index - other.index ;
                }
                
                inline value_type operator*() {
                    return apply( Sequence() ) ;
                }
                
                inline bool operator==( const MapplyIterator& other ){ return index == other.index; }
                inline bool operator!=( const MapplyIterator& other ){ return index != other.index; }
                
            private:
                IteratorsTuple iterators ;
                Function fun ;
                int index ;
                bool any_prim_na ;
                
                template <typename... Pack>
                void nothing( Pack... pack ){}
                
                template <int... S>
                void increment_all(Rcpp::traits::sequence<S...>) {
                    nothing( increment<S>()... ) ;    
                }
                
                template <int... S>
                void increment_all(int n, Rcpp::traits::sequence<S...>) {
                    nothing( increment<S>(n)... ) ;    
                }
                
                template <int... S>
                void decrement_all(Rcpp::traits::sequence<S...>) {
                    nothing( decrement<S>()... ) ;    
                }
                
                template <int... S>
                void decrement_all(int n, Rcpp::traits::sequence<S...>) {
                    nothing( decrement<S>(n)... ) ;    
                }
                
                template <int S>
                int increment(){
                    ++std::get<S>(iterators) ;
                    return 0  ;
                }
                
                template <int S>
                int increment(int n){
                    std::get<S>(iterators) += n;
                    return 0  ;
                }
                
                template <int S>
                int decrement(){
                    --std::get<S>(iterators) ;
                    return 0  ;
                }
                
                template <int S>
                int decrement(int n){
                    std::get<S>(iterators) -= n;
                    return 0  ;
                }
                
                template <int... S>
                value_type apply(Rcpp::traits::sequence<S...>) {
                    ETuple values( *std::get<S>(iterators) ... ) ;
                    if( any_prim_na || any_na( values, not_prim_sequence() ) ) return NA ;
                    return internal::caster<real_value_type,value_type>(fun( std::get<S>(values)... )) ;
                } 
                 
                template <int... S>
                IteratorsTuple get_iterators(const Tuple& data, int pos, Rcpp::traits::sequence<S...>){
                    return std::make_tuple( get_iterator<S>( data, pos, 
                        typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type >::type()
                    ) ... ) ;    
                }
                   
                template <int INDEX>
                inline typename std::tuple_element<INDEX,IteratorsTuple>::type get_iterator( const Tuple& data, int pos, std::true_type ) const {
                    return typename std::tuple_element<INDEX,IteratorsTuple>::type( std::get<INDEX>(data), 0 ) ; 
                }
                
                template <int INDEX>
                inline typename std::tuple_element<INDEX,IteratorsTuple>::type get_iterator( const Tuple& data, int pos, std::false_type ) const {
                    return sugar_begin( std::get<INDEX>(data) ) + pos ;
                }

            } ;
            
            typedef MapplyIterator const_iterator ;
            
            Mapply( Function fun_, Args&&... args ) :
                data( args... ),
                fun(fun_),
                n(get_size()), 
                any_prim_na( any_na(data, prim_sequence() ) )
            {
                RCPP_DEBUG( "Mapply = %s\n", DEMANGLE(Mapply) )
                RCPP_DEBUG( "Tuple  = %s\n", DEMANGLE(Tuple) )
                RCPP_DEBUG( "ETuple = %s\n", DEMANGLE(ETuple) ) 
                RCPP_DEBUG( "ITuple = %s\n", DEMANGLE(IteratorsTuple) )
            }

            inline R_xlen_t size() const {
                return n ;
            }
            inline const_iterator begin() const { return const_iterator( data, fun, any_prim_na, 0) ; }
            inline const_iterator end() const { return const_iterator( data, fun, any_prim_na, size() ) ; }
               
            template <typename Target>
            void apply( Target& target ) const {
                if(any_prim_na){
                    std::fill( target.begin(), target.end(), static_cast<typename Target::value_type>(NA) ) ;
                } else {
                    typedef typename traits::r_vector_element_converter< Target::r_type::value >::type converter ;
                    std::transform( begin(), end(), target.begin(), [](value_type x){
                            return converter::get(x) ;
                    });  
                }
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                if(any_prim_na){
                    std::fill( target.begin(), target.end(), static_cast<typename Target::value_type>(NA) ) ;
                } else {
                    typedef typename traits::r_vector_element_converter< Target::r_type::value >::type converter ;
                    parallel::transform( begin(), end(), target.begin(), [](value_type x){
                            return converter::get(x) ;
                    });  
                }
            }
            
        private: 
            inline int get_size() const {
                return get_size_impl( Sequence() ) ;    
            }
            
            template <int... S>
            R_xlen_t get_size_impl(Rcpp::traits::sequence<S...>) const {
                auto sizes = { 
                    get_ith_size<S>(
                        typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type >::type()
                    ) ... 
                } ;
                return *std::max_element( std::begin(sizes), std::end(sizes) ) ;
            }
            
            template <int INDEX>
            constexpr R_xlen_t get_ith_size( std::true_type ) const {
                return 1 ;     
            }
            
            template <int INDEX>
            R_xlen_t get_ith_size( std::false_type ) const {
                return std::get<INDEX>(data).size() ;     
            }
            
        } ;

    } // sugar

    template <typename Function,typename... Args>
    typename sugar::Mapply<Function,Args...>
    mapply( Function fun, Args&&... args ){
        return sugar::Mapply<Function,Args...>( fun, std::forward<Args>(args) ... ) ;
    }

    template <typename Function,typename... Args>
    auto Map( Function fun, Args&&... args ) -> decltype(map(fun, std::forward<Args>(args)... )){
        return map(fun, std::forward<Args>(args)... ) ;
    }

} // Rcpp

#endif
