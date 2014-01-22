#ifndef Rcpp__vector_create_h
#define Rcpp__vector_create_h

namespace Rcpp{
    
template <int RTYPE, typename... Args>
class Create {
    typedef typename traits::r_vector_element_converter<RTYPE>::type converter_type ;
    typedef Vector<RTYPE> Vec ;
    
    public:
        Create( Args... args ) : data( (int)sizeof...(Args) ) {
            set_value( traits::number_to_type<sizeof...(Args)>(), 0, args...) ;
        }
        operator Vec(){ return data ; }
        
    private:
        template <typename T, typename... Pack>
        inline void set_value( traits::number_to_type<sizeof...(Pack) + 1>, int i, const T& obj, const Pack&... pack ){
            data[i] = converter_type::get(obj) ;
            set_value( typename traits::number_to_type< sizeof...(Pack) >() , i+1, pack... ) ;
        }
        
        inline void set_value( traits::number_to_type<0>, int /* i */ ){}
        
        Vec data ;
} ;  

template <int RTYPE, typename... Args>
class CreateWithNames {
    typedef typename traits::r_vector_element_converter<RTYPE>::type converter_type ;
    typedef Vector<RTYPE> Vec ;
    
    public:
        CreateWithNames( Args... args ) : 
            data( (int)sizeof...(Args)), 
            names( (int)sizeof...(Args))
        {
            if( sizeof...(Args) ){
                set_value( traits::number_to_type<sizeof...(Args)>(), 0, args...) ;
            }
            data.names() = names ;
        }
        
        operator Vec(){ return data ; }
        
    private:
        template <typename T, typename... Pack>
        inline void set_value( traits::number_to_type<sizeof...(Pack) + 1>, int i, const T& obj, const Pack&... pack ){
            data[i] = converter_type::get(obj) ;
            names[i] = Rf_mkChar( internal::get_object_name(obj) ) ;
            set_value( typename traits::number_to_type< sizeof...(Pack) >() , i+1, pack... ) ;
        }
        
        inline void set_value( traits::number_to_type<0>, int /* i */){}
        
        
        Vec data ;
        CharacterVector names ;
} ;  

template <int RTYPE, typename... Args>
struct create_type {
    typedef typename std::conditional<
        traits::any_named<Args...>::type::value, 
        CreateWithNames<RTYPE, Args...>,
        Create<RTYPE, Args...>
    >::type type ;
} ;

}
#endif
