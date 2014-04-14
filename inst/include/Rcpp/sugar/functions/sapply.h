#ifndef Rcpp__sugar__sapply_h
#define Rcpp__sugar__sapply_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T, typename Function, bool NO_CONVERSION>
class Sapply : public SugarVectorExpression< 
    Rcpp::traits::r_sexptype_traits<
        typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type
    >::rtype , 
    true ,
    Sapply<RTYPE,NA,T,Function,NO_CONVERSION>
>, public custom_sugar_vector_expression {
public:
    typedef typename Rcpp::traits::storage_type<RTYPE>::type VEC_STORAGE;
    typedef typename std::result_of<Function(VEC_STORAGE)>::type result_type ; 

    const static int RESULT_R_TYPE = 
        Rcpp::traits::r_sexptype_traits<result_type>::rtype ;

    typedef Rcpp::VectorBase<RTYPE,NA,T> VEC ;
    typedef typename Rcpp::traits::r_vector_element_converter<RESULT_R_TYPE>::type converter_type ;
    typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type STORAGE ;

    Sapply( const VEC& vec_, Function fun_ ) : vec(vec_), fun(fun_){}

    inline STORAGE operator[]( int i ) const {
        return converter_type::get( fun( vec[i] ) );
    }
    inline int size() const { return vec.size() ; }

    template <typename Target>
    inline void apply( Target& target ) const {
        std::transform( sugar_begin(vec), sugar_end(vec), target.begin(), [this]( VEC_STORAGE x){
            return converter_type::get( fun(x) ) ;       
        }) ;     
    }
    
private:
    const VEC& vec ;
    Function fun ;

} ;


template <int RTYPE, bool NA, typename T, typename Function>
class Sapply<RTYPE,NA,T,Function,true> : public SugarVectorExpression< 
    Rcpp::traits::r_sexptype_traits<
        typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type
    >::rtype , 
    true ,
    Sapply<RTYPE,NA,T,Function,true>
>, public custom_sugar_vector_expression {
public:
    typedef typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type result_type ; 
    const static int RESULT_R_TYPE = 
        Rcpp::traits::r_sexptype_traits<result_type>::rtype ;

    typedef Rcpp::VectorBase<RTYPE,NA,T> VEC ;
    typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type STORAGE ;

    Sapply( const VEC& vec_, Function fun_ ) : vec(vec_.get_ref()), fun(fun_){
        RCPP_DEBUG( "Sapply  = %s", DEMANGLE(Sapply) )
    }

    inline STORAGE operator[]( int i ) const {
        return fun( vec[i] ) ;
    }
    inline int size() const { return vec.size() ; }

    template <typename Target>
    inline void apply( Target& target ) const {
        std::transform( sugar_begin(vec), sugar_end(vec), target.begin(), fun ) ;     
    }
    
private:
    const VEC& vec ;
    Function fun ;

} ;


} // sugar

template <int RTYPE, bool NA, typename T, typename Function >
inline sugar::Sapply<
    RTYPE,NA,T,Function, 
    std::is_same< 
        typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type )>::type ,  
        typename Rcpp::traits::storage_type< traits::r_sexptype_traits< typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type >::rtype >::type
    >::value
> 
sapply( const Rcpp::VectorBase<RTYPE,NA,T>& t, Function fun ){
    typedef typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type result_type ; 
    return sugar::Sapply<RTYPE,NA,T,Function, 
    std::is_same< 
        result_type,  
        typename Rcpp::traits::storage_type< traits::r_sexptype_traits<result_type>::rtype >::type
    >::value >( t, fun ) ;
}

} // Rcpp

#endif
