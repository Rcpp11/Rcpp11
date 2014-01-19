#ifndef RCPP_ATTRIBUTES_delete_all_H
#define RCPP_ATTRIBUTES_delete_all_H

namespace Rcpp{

    template <typename T, typename = typename std::enable_if<std::is_pointer<typename T::value_type>::value>::type >
    void delete_all( T& x){
        try{
            for( auto ptr: x) delete ptr ;
            x.clear() ;
        } catch(...){}
    }
    
}

#endif
