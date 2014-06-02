#ifndef Rcpp__sugar__mapply_h
#define Rcpp__sugar__mapply_h

namespace Rcpp{
    namespace sugar{

        template <typename T>
        class fake_iterator{
        public:
            fake_iterator( const T& value_) : value(value_){}
            fake_iterator& operator++(){ return *this ; }

            inline T operator*() {
                return value ;
            }

        private:
            T value ;
        } ;
        
        template <typename input_type, bool>
        struct mapply_iterator ;
        
        template <typename input_type>
        struct mapply_iterator<input_type, true> {
            typedef fake_iterator<input_type> type ;
        } ;
        
        template <typename input_type>
        struct mapply_iterator<input_type, false> {
            typedef typename Rcpp::sugar::sugar_iterator_type<input_type>::type type ;
        } ;
        
        template <
            typename Function,
            typename... Args
        >
        class Mapply :
            public SugarVectorExpression<Mapply<Function,Args...>>,
            public custom_sugar_vector_expression
        {
        public:
            const static int N = sizeof...(Args);
            typedef typename Rcpp::traits::index_sequence<Args...>::type Sequence ;
            typedef std::tuple<Args...> Tuple ;
            typedef std::tuple< typename mapply_scalar_type<Args>::type ... > ETuple ;
            typedef typename std::result_of<Function(typename mapply_scalar_type<Args>::type ...)>::type value_type ;

        private:
            Tuple data ;
            Function fun ;
            R_xlen_t n ;

            typedef std::tuple< 
                typename mapply_iterator<
                    typename std::decay<Args>::type, 
                    Rcpp::traits::is_primitive<Args>::type::value
                >::type ...
            > IteratorsTuple ;
            
        public:
            Mapply( Function fun_, Args&&... args ) :
                data( std::forward<Args>(args)... ),
                fun(fun_),
                n(get_size()){}

            inline value_type operator[]( R_xlen_t i ) const {
                return eval(i, Sequence() );
            }
            inline R_xlen_t size() const {
                return n ;
            }

            template <typename Target>
            inline void apply( Target& target ) const {
                auto iterators = get_iterators( Sequence() ) ;
                auto it = target.begin() ;
                for( R_xlen_t i=0; i<n; i++) set_values( it, iterators, Sequence() ) ;
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
                return *std::max_element( begin(sizes), end(sizes) ) ;
            }
            
            template <int INDEX>
            constexpr R_xlen_t get_ith_size( std::true_type ) const {
                return 1 ;     
            }
            
            template <int INDEX>
            R_xlen_t get_ith_size( std::false_type ) const {
                return std::get<INDEX>(data).size() ;     
            }
            
            
            // methods used for the implementation of operator[]
            template <int... S>
            inline value_type eval( R_xlen_t i, Rcpp::traits::sequence<S...> ) const {
                return fun(
                    get_ith<S>(i, typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type >::type() ) ...
                );
            }

            template <int INDEX>
            inline typename std::tuple_element<INDEX,ETuple>::type get_ith( R_xlen_t , std::true_type ) const {
                return std::get<INDEX>(data) ;
            }

            template <int INDEX>
            inline typename std::tuple_element<INDEX,ETuple>::type get_ith( R_xlen_t i, std::false_type ) const {
                return std::get<INDEX>(data)[i] ;
            }

            // methods used for the implementation of apply
            // in essence, set_values extract data by dereferencing and incrementing the iterators from the pack
            // then calls the function and store the result into the target iterator
            template <typename Iterator, typename Pack, int... S>
            inline void set_values( Iterator& it, Pack& iterators, Rcpp::traits::sequence<S...> ) const {
                *it = fun( extract( std::get<S>(iterators) ) ... ) ;
                ++it ;
            }

            template <typename It>
            auto extract( It& it) const -> decltype(*it){
                decltype(*it) val = *it ;
                ++it ;
                return val ;
            }

            template <int INDEX>
            inline typename std::tuple_element<INDEX,IteratorsTuple>::type get_iterator( std::true_type ) const {
                return typename std::tuple_element<INDEX,IteratorsTuple>::type( std::get<INDEX>(data) ) ;
            }

            template <int INDEX>
            inline typename std::tuple_element<INDEX,IteratorsTuple>::type get_iterator( std::false_type ) const {
                return sugar_begin( std::get<INDEX>(data) ) ;
            }

            template <int... S>
            inline IteratorsTuple get_iterators( Rcpp::traits::sequence<S...> ) const {
                return std::make_tuple( get_iterator<S>(
                    typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type >::type()
                    ) ... ) ;
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
