#ifndef Rcpp__sugar_lazy_create_h
#define Rcpp__sugar_lazy_create_h

namespace Rcpp{
    
    template <typename T>
    struct create_proxy_class {
        typedef T type ;    
    } ;
    
    template <int N>
    struct create_proxy_class<const char[N]> {
        typedef String type ;    
    } ;
    
    template <int RTYPE, typename... Args>
    class Create : public LazyVector<RTYPE, Create<RTYPE,Args...>> {
        typedef typename traits::r_vector_element_converter<RTYPE>::type converter_type ;
        typedef std::tuple<Args...> Tuple ;
        public:
            Create( Args... args ) : data( args... ) {}
            
            inline int size() const {
                return sizeof...(Args) ;    
            }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                set_value<0, typename Target::iterator >( it, std::true_type() ) ;            
            }
            
        private:
            template <int INDEX, typename Iterator>
            inline void set_value( Iterator& it, std::true_type ) const {
                *it = converter_type::get( std::get<INDEX>(data) ) ; ++it ;
                
                set_value<INDEX+1, Iterator>( it, 
                    typename std::integral_constant<bool, (INDEX+1 < sizeof...(Args)) >::type()
                ) ;
            }
            
            template <int INDEX, typename Iterator>
            inline void set_value( Iterator& it, std::false_type ) const {}
            
            Tuple data ;
    } ;  
    
    template <typename... Args>
    class Create<-1,Args...> : public LazyVector<-1,Create<-1,Args...>> {
        public:
            Create( Args... args ){} 
            
            inline int size() const {
                return sizeof...(Args) ;    
            }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                for( int i=0; i<size(); i++, ++it) *it = NA ;
            }
    } ;
    
    
    template <int RTYPE, typename... Args>
    class CreateWithNames : public LazyVector<RTYPE, CreateWithNames<RTYPE,Args...>>{
        typedef typename traits::r_vector_element_converter<RTYPE>::type converter_type ;
        
        public:
            CreateWithNames( Args... args ) : data( args... ) {}
            
            inline int size() const {
                return sizeof...(Args) ;    
            }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                Shield<SEXP> names = Rf_allocVector( STRSXP, sizeof...(Args) ) ;
                set_value<0, typename Target::iterator >( names, it, std::true_type() ) ;    
                target.names() = names ;
            }
            
        private:
            
            template <int INDEX, typename Iterator>
            inline void set_value( Shield<SEXP>& names, Iterator& it, std::true_type ) const {
                auto val = std::get<INDEX>(data) ;
                *it = converter_type::get(val) ; ++it ;
                SET_STRING_ELT(names, INDEX, Rf_mkChar( internal::get_object_name(val) ) );
                
                set_value<INDEX+1,Iterator>( names, it, 
                    typename std::integral_constant<bool, (INDEX+1 < sizeof...(Args)) >::type() 
                    ) ;
            }
            
            template <int INDEX, typename Iterator>
            inline void set_value( Shield<SEXP>& names, Iterator& it, std::false_type ) const {}
            
            std::tuple<Args...> data ;
            
    } ;  
    
    template <typename... Args>
    class CreateWithNames<-1,Args...> : public LazyVector<-1, CreateWithNames<-1,Args...>>{
    public:
        CreateWithNames( Args... args ) : data( args... ) {}
        
        inline int size() const {
            return sizeof...(Args) ;    
        }
        
        template <typename Target>
        inline void apply( Target& target ) const {
            auto it = target.begin() ;
            Shield<SEXP> names = Rf_allocVector( STRSXP, sizeof...(Args) ) ;
            set_value<0, typename Target::iterator >( names, it, std::true_type() ) ;    
            target.names() = names ;
        }
        
    private:
        
        template <int INDEX, typename Iterator>
        inline void set_value( Shield<SEXP>& names, Iterator& it, std::true_type ) const {
            auto val = std::get<INDEX>(data) ;
            *it = NA ; ++it ;
            SET_STRING_ELT(names, INDEX, Rf_mkChar( internal::get_object_name(val) ) );
            
            set_value<INDEX+1,Iterator>( names, it, 
                typename std::integral_constant<bool, (INDEX+1 < sizeof...(Args)) >::type() 
                ) ;
        }
        
        template <int INDEX, typename Iterator>
        inline void set_value( Shield<SEXP>& names, Iterator& it, std::false_type ) const {}
            
        std::tuple<Args...> data ;
            
    } ;
    
       
    template <int RTYPE>
    class EmptyCreate : public LazyVector<RTYPE, EmptyCreate<RTYPE> >{
    public:
        inline int size() const { return 0; }
          
        template <typename Target>
        inline void apply( Target& target ) const {}
        
    } ;
    
    template <int RTYPE, typename... Args>
    struct create_type {
        typedef typename std::conditional<
            sizeof...(Args) == 0, 
            EmptyCreate<RTYPE>,
            typename std::conditional<
                traits::any_named<Args...>::type::value, 
                CreateWithNames<RTYPE, Args...>,
                Create<RTYPE, Args...>
            >::type
        >::type type ;
    } ;
    
    template <typename... Args> struct create_r_type ;
    
    template <typename First, typename... Args>
    struct create_r_type<First,Args...> {
        const static int first_r_type = traits::get_compatible_r_vector_type<First>::rtype ; 
        const static int second_r_type = create_r_type<Args...>::type::value ; 
        
        typedef typename std::conditional<
            (first_r_type<second_r_type), 
            std::integral_constant<int,second_r_type>, 
            std::integral_constant<int,first_r_type>
        >::type type ;
    } ;
    
    template <typename First>
    struct create_r_type<First> {
        typedef typename std::integral_constant<int, traits::get_compatible_r_vector_type<First>::rtype>::type type ;
    } ;
    
    template <typename... Args>
    typename create_type< create_r_type<Args...>::type::value , typename create_proxy_class<Args>::type ... >::type
    create( Args... args ){
        typedef typename create_type<
            create_r_type<Args...>::type::value,
            typename create_proxy_class<Args>::type ...
        >::type Creator ;
        return Creator( typename create_proxy_class<Args>::type(args) ...) ;
    }
    
    template <typename... Args>
    typename create_type< VECSXP , Args...>::type
    list( Args... args){
        return typename create_type< VECSXP , Args...>::type(args...) ;
    }
    
}
#endif
