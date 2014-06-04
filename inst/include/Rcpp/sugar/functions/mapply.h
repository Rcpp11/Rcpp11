#ifndef Rcpp__sugar__mapply_h
#define Rcpp__sugar__mapply_h

namespace Rcpp{
    namespace sugar{

        template <typename input_type, bool>
        struct mapply_iterator_dispatch ;
        
        template <typename input_type>
        struct mapply_iterator_dispatch<input_type, true> {
            typedef constant_iterator<input_type> type ;
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
        
        template <
            typename Function,
            typename... Args
        >
        class Mapply :
            public SugarVectorExpression<
                typename std::result_of<Function(typename traits::mapply_scalar_type<Args>::type ...)>::type, 
                Mapply<Function,Args...>
            > // , public custom_sugar_vector_expression
        {
        public:
            const static int N = sizeof...(Args);
            typedef typename Rcpp::traits::index_sequence<Args...>::type Sequence ;
            typedef std::tuple<Args...> Tuple ;
            typedef std::tuple< typename traits::mapply_scalar_type<Args>::type ... > ETuple ;
            typedef typename std::result_of<Function(typename traits::mapply_scalar_type<Args>::type ...)>::type value_type ;
            typedef std::tuple< typename mapply_iterator<Args>::type ... > IteratorsTuple ;
            
        private:
            Tuple data ;
            Function fun ;
            R_xlen_t n ;

        public:
            
            class MapplyIterator {
            public:
                MapplyIterator( const Tuple& data, const Function& fun_, int pos = 0 ) : 
                    iterators( get_iterators(data, pos, Sequence() ) ), fun(fun_), index(pos)
                {}
                
                inline MapplyIterator& operator++(){
                    increment_all( Sequence() ) ;
                    ++index ;
                    return *this ;
                }
                
                MapplyIterator operator+( int n){
                    MapplyIterator copy(*this) ;
                    for(int i=0; i<n; i++) ++copy ;
                    return copy;
                }
                
                inline value_type operator*() {
                    return apply( Sequence() ) ;
                }
                
                inline bool operator==( const MapplyIterator& other ){ return index == other.index; }
                inline bool operator!=( const MapplyIterator& other ){ return index != other.index; }
                
            private:
                IteratorsTuple iterators ;
                const Function& fun ;
                int index ;
                
                template <int... S>
                void increment_all(Rcpp::traits::sequence<S...>) {
                    nothing( increment<S>()... ) ;    
                }
                
                template <typename... Pack>
                void nothing( Pack... pack ){}
                
                template <int S>
                int increment(){
                    ++std::get<S>(iterators) ;
                    return 0  ;
                }
                
                template <int... S>
                value_type apply(Rcpp::traits::sequence<S...>) {
                    return fun( *std::get<S>(iterators) ... ) ;
                } 
                 
                template <int... S>
                IteratorsTuple get_iterators(const Tuple& data, int pos, Rcpp::traits::sequence<S...>){
                    return std::make_tuple( get_iterator<S>( data, pos, 
                        typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type >::type()
                    ) ... ) ;    
                }
                   
                template <int INDEX>
                inline typename std::tuple_element<INDEX,IteratorsTuple>::type get_iterator( const Tuple& data, int pos, std::true_type ) const {
                    typedef typename std::tuple_element<INDEX,IteratorsTuple>::type Iter ; 
                    return Iter( std::get<INDEX>(data) ) + pos; 
                }
                
                template <int INDEX>
                inline typename std::tuple_element<INDEX,IteratorsTuple>::type get_iterator( const Tuple& data, int pos, std::false_type ) const {
                    return sugar_begin( std::get<INDEX>(data) ) + pos ;
                }

            } ;
            
            typedef MapplyIterator const_iterator ;
            
            Mapply( Function fun_, Args&&... args ) :
                data( std::forward<Args>(args)... ),
                fun(fun_),
                n(get_size()){}

            inline R_xlen_t size() const {
                return n ;
            }
            inline const_iterator begin() const { return const_iterator( data, fun, 0 ) ; }
            inline const_iterator end() const { return const_iterator( data, fun, size() ) ; }
            
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
    typename sugar::Mapply<Function,Args...>
    Map( Function fun, Args&&... args ){
        return sugar::Mapply<Function,Args...>( fun, std::forward<Args>(args) ... ) ;
    }

} // Rcpp

#endif
