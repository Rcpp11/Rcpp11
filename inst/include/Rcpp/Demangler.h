#ifndef Rcpp__Demangler__h
#define Rcpp__Demangler__h

namespace Rcpp{

    template <typename T>
    struct Demangler {
        static std::string get(){ return demangle( typeid(T).name() ) ; }
    } ;
    template <int N>
    struct Demangler< char[N] > {
        static std::string get(){ 
          std::stringstream ss  ;
          ss << "char[" 
             << N 
             << "]" ;
          return ss.str() ;
        }
    } ;
    
    
    #define DEMANGLE_ECHO(__TYPE__)                                 \
    template <>                                                     \
    struct Demangler<__TYPE__>{                                     \
        static std::string get(){ return std::string(#__TYPE__) ; } \
    } ;
    
    #define DEMANGLE_CONTAINER_1(__CONTAINER__)    \
    template <typename T>                          \
    struct Demangler< __CONTAINER__<T> >{          \
        static std::string get(){                  \
            std::string res( #__CONTAINER__ ) ;    \
            res += "<" ;                           \
            res += Demangler<T>::get() ;           \
            res += ">" ;                           \
            return res;                            \
        }                                          \
    } ;                                            
    
    #define DEMANGLE_CONTAINER_2(__CONTAINER__)    \
    template <typename KEY, typename VALUE>        \
    struct Demangler< __CONTAINER__<KEY,VALUE> >{  \
        static std::string get(){                  \
            std::string res( #__CONTAINER__ ) ;    \
            res += "<" ;                           \
            res += Demangler<KEY>::get() ;         \
            res += "," ;                           \
            res += Demangler<VALUE>::get() ;       \
            res += ">" ;                           \
            return res;                            \
        }                                          \
    } ;                                            
    
    #define DEMANGLE_CONTAINER_ADAPTOR_1(__CONTAINER__)    \
    template <typename T, typename Container>              \
    struct Demangler< __CONTAINER__<T,Container> >{        \
        static std::string get(){                          \
            std::string res( #__CONTAINER__ ) ;            \
            res += "<" ;                              \
            res += Demangler<T>::get() ;                   \
            res += "," ;                      \
            res += Demangler<Container>::get() ;           \
            res += ">" ;                                   \
            return res;                                    \
        }                                                  \
    } ;                                            
    
    DEMANGLE_ECHO(std::string)  
    
    DEMANGLE_CONTAINER_1(std::vector)
    DEMANGLE_CONTAINER_1(std::list)
    DEMANGLE_CONTAINER_1(std::forward_list)
    DEMANGLE_CONTAINER_1(std::set)
    DEMANGLE_CONTAINER_1(std::deque)
    DEMANGLE_CONTAINER_1(std::unordered_set)
    
    DEMANGLE_CONTAINER_2(std::map)
    DEMANGLE_CONTAINER_2(std::unordered_map)
         
    DEMANGLE_CONTAINER_ADAPTOR_1(std::queue)
    DEMANGLE_CONTAINER_ADAPTOR_1(std::priority_queue)
    DEMANGLE_CONTAINER_ADAPTOR_1(std::stack)
    
    // namespace internal {
    //       
    //     template <typename... Args>
    //     struct Demangle_Part ;
    //     
    //     template <typename First>
    //     struct Demangle_Part<First>{
    //         static void get( std::string& s){
    //             s += Demangler<First>::get() ;   
    //         }
    //     };
    //     template <typename First, typename... Args> 
    //     struct Demangle_Part<First, Args...>{
    //         static void get( std::string& s ){
    //             s += Demangler<First>::get() ;
    //             s += ", " ;
    //             Demangle_Part<Args...>::get(s);
    //         }
    //     };
    //     
    // }
    
    // template <typename... Args>
    // struct Demangler<std::tuple<Args...>>{
    //     static std::string get(){
    //         std::string res( "std::tuple<" ) ;
    //         internal::Demangle_Part<Args...>::get(res) ; 
    //         res += ">" ;
    //         return res ;
    //     }
    // };
    
    
} // Rcpp 

#endif
