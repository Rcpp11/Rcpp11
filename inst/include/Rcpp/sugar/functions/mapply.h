#ifndef Rcpp__sugar__mapply_h
#define Rcpp__sugar__mapply_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T, bool>
        struct mapply_input_type ;
        
        template <typename T>
        struct mapply_input_type<T,true> {
            typedef typename std::decay<T>::type type ;
        } ;                                   
        template <typename T>
        struct mapply_input_type<T,false> {
            typedef typename std::decay<T>::type::stored_type type ;
        } ;
        
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
        
        template <
            typename Function,
            typename... Args
        >
        class Mapply : 
            public SugarVectorExpression< 
                Rcpp::traits::r_sexptype_traits<
                    typename std::result_of<Function(typename mapply_input_type<Args, Rcpp::traits::is_primitive<Args>::type::value >::type ...)>::type
                >::rtype , 
                true ,
                Mapply<Function,Args...>
            >, 
            public custom_sugar_vector_expression 
        {
        public:   
            typedef typename Rcpp::traits::index_sequence<Args...>::type Sequence ;
            typedef std::tuple<Args...> Tuple ;
            typedef std::tuple< typename mapply_input_type<Args, Rcpp::traits::is_primitive<Args>::type::value >::type ... > ETuple ;
            
            typedef typename std::result_of<Function(typename mapply_input_type<Args, Rcpp::traits::is_primitive<Args>::type::value >::type ...)>::type result_type ;
        
            Mapply( Function fun_, Args&&... args ) : 
                data( std::forward<Args>(args)... ), 
                fun(fun_), 
                n(std::get<0>(data).size()){}
        
            inline result_type operator[]( int i ) const {
                return eval(i, Sequence() );
            }
            inline int size() const { 
                return n ; 
            }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                auto iterators = get_iterators( Sequence() ) ; 
                auto it = target.begin() ;
                for( int i=0; i<n; i++) set_values( it, iterators, Sequence() ) ;
            }
        
        private:
            Tuple data ;
            Function fun ;
            int n ;
                   
            // methods used for the implementation of operator[]
            template <int... S>
            inline result_type eval( int i, Rcpp::traits::sequence<S...> ) const {
                return fun( 
                    get_ith<S>(i, typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type >::type() ) ... 
                );    
            }
            
            template <int INDEX>
            inline typename std::tuple_element<INDEX,ETuple>::type get_ith( int , std::true_type ) const {
                return std::get<INDEX>(data) ;
            }
            
            template <int INDEX>
            inline typename std::tuple_element<INDEX,ETuple>::type get_ith( int i, std::false_type ) const {
                return std::get<INDEX>(data)[i] ;
            }
            
            // methods used for the implementation of apply
            // in essence, set_values extract data by dereferencing and incrementing the iterators from the pack
            // then calls the function and store the result into the target iterator
            template <typename Iterator, typename Pack, int... S>
            void set_values( Iterator& it, Pack& iterators, Rcpp::traits::sequence<S...> ) const {
                *it = fun( extract<S, typename std::tuple_element<S,Pack>::type >( std::get<S>(iterators) ) ... ) ;
                ++it ;
            }
            
            template <int INDEX, typename It>
            auto extract( It& it) const -> decltype(*it){
                decltype(*it) val = *it ;
                ++it ;
                return val ;
            }
            
            template <int INDEX>
            inline fake_iterator< typename std::tuple_element<INDEX,Tuple>::type > get_iterator( std::true_type ) const {
                return fake_iterator< typename std::tuple_element<INDEX,Tuple>::type >( std::get<INDEX>(data) ) ;    
            }
            
            template <int INDEX>
            inline auto get_iterator( std::false_type ) const -> decltype( sugar_begin( std::get<INDEX>(data) ) ) {
                return sugar_begin( std::get<INDEX>(data) ) ;    
            }
            
            template <int... S>
            inline auto get_iterators( Rcpp::traits::sequence<S...>  ) const -> decltype( std::make_tuple( get_iterator<S>( typename Rcpp::traits::is_primitive< typename std::tuple_element<S,Tuple>::type >::type()) ... ) ) {
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

} // Rcpp

#endif
