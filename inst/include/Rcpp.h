#ifndef Rcpp11_h
#define Rcpp11_h

// #define RCPP_DEBUG_LEVEL 1

#include <cmath>
#include <csetjmp>

#include <initializer_list>
#include <unordered_map>
#include <unordered_set>

#include <Rcpp/macros/macros.h>
#include <Rcpp/R.h>

#include <Rcpp/routines.h>
#include <Rcpp/wrap/forward.h>

#include <Rcpp/protection/protection.h>

#define RCPP_SET_VECTOR_ELT SET_VECTOR_ELT 
// #define RCPP_SET_VECTOR_ELT(v,i,x) { Rprintf("SET_VECTOR_ELT(%p, %d, %p). file = %s, line = %d\n", (SEXP)v, i, (SEXP)x, __FILE__, __LINE__) ; SET_VECTOR_ELT( (SEXP)v,i,(SEXP)x) ; } 

#include <cstdint>
#include <array>
#include <type_traits>
#include <iterator>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <cxxabi.h>

#include <map>
#include <set>
#include <stdexcept>
#include <vector>
#include <deque>
#include <functional>
#include <numeric>
#include <algorithm>
#include <complex>
#include <limits>
#include <typeinfo>
#include <tuple>
#include <utility>
#include <future>
#include <Rcpp/complex.h>

#include <Rcpp/exceptions.h>
#include <Rcpp/Demangler.h>

namespace Rcpp{
    
    inline const char* short_file_name(const char* file) {
        std::string f(file) ;
        return f.substr( f.find_last_of("/") + 1 ).c_str() ;
    }

    class String ;
    template <typename CLASS> class PreserveStorage ;
    template <typename CLASS> class NoProtectStorage ;
    
    template <int RTYPE, template <class> class StoragePolicy = PreserveStorage> 
    class Vector ;
    
    using CharacterVector = Vector<STRSXP> ;
    using List = Vector<VECSXP> ; 
    using ExpressionVector = Vector<EXPRSXP> ; 
    
    RCPP_API_CLASS_DECL(RObject) 
    RCPP_API_CLASS_DECL(Language) 
    RCPP_API_CLASS_DECL(Pairlist) ;
    RCPP_API_CLASS_DECL(Environment) ;
    RCPP_API_CLASS_DECL(Promise) ;
    RCPP_API_CLASS_DECL(WeakReference) ;
    RCPP_API_CLASS_DECL(S4) ;
    RCPP_API_CLASS_DECL(Formula) ;
    RCPP_API_CLASS_DECL(Reference) ;
    RCPP_API_CLASS_DECL(Function) ;
    
    template < template <class> class StoragePolicy > class Symbol_Impl ;
    using Symbol = Symbol_Impl<NoProtectStorage> ;
    
    template < template <class> class StoragePolicy > class DataFrame_Impl ;
    using DataFrame = DataFrame_Impl<PreserveStorage> ;
    
}	
namespace Rcpp{
    inline SEXP Rcpp_PreserveObject(SEXP x){ 
        if( x != R_NilValue ) {
            R_PreserveObject(x); 
        }
        return x ;
    }

    inline void Rcpp_ReleaseObject(SEXP x){
        if (x != R_NilValue) {
            R_ReleaseObject(x); 
        }
    }

    inline SEXP Rcpp_ReplaceObject(SEXP x, SEXP y){
        if( x == R_NilValue ){
            Rcpp_PreserveObject( y ) ;    
        } else if( y == R_NilValue ){
            Rcpp_ReleaseObject( x ) ;
        } else {
            // if we are setting to the same SEXP as we already have, do nothing 
            if (x != y) {
                
                // the previous SEXP was not NULL, so release it 
                Rcpp_ReleaseObject(x);
                
                // the new SEXP is not NULL, so preserve it 
                Rcpp_PreserveObject(y);
            }
        }
        return y ;
    } 
    
    template <typename T> T as( SEXP ) ;
}

#include <Rcpp/internal/na.h>
#include <Rcpp/traits/traits.h>
#include <Rcpp/Named.h>

#include <Rcpp/internal/caster.h>
#include <Rcpp/internal/r_vector.h>
#include <Rcpp/r_cast.h>

#include <Rcpp/internal/export.h>
#include <Rcpp/internal/r_coerce.h>
#include <Rcpp/as.h>
#include <Rcpp/InputParameter.h>
#include <Rcpp/is.h>

#include <Rcpp/vector/VectorBase.h>

#include <Rcpp/wrap/wrap.h>

#include <Rcpp/internal/Proxy_Iterator.h>
#include <Rcpp/internal/const_Proxy_Iterator.h>
#include <Rcpp/internal/converter.h>

#include <Rcpp/sugar/sugar_forward.h>

#include <Rcpp/longlong.h>
#include <Rcpp/transient_vector.h>

#include <Rcpp/registration/registration.h>

#include <Rcpp/exceptions.h>

#include <Rcpp/proxy/proxy.h>
#include <Rcpp/storage/storage.h>

#include <Rcpp/storage/PreserveStorage.h>
#include <Rcpp/storage/NoProtectStorage.h>

#include <Rcpp/Node.h>
#include <Rcpp/DottedPairImpl.h>

#include <Rcpp/structure.h>

#include <Rcpp/RObject.h>

#include <Rcpp/Promise.h>
#include <Rcpp/S4.h>
#include <Rcpp/Reference.h>
#include <Rcpp/clone.h>
#include <Rcpp/grow.h>
#include <Rcpp/Environment.h>
#include <Rcpp/Evaluator.h>

#include <Rcpp/Vector.h>
#include <Rcpp/sugar/nona/nona.h>
#include <Rcpp/Extractor.h>

#include <Rcpp/XPtr.h>
#include <Rcpp/Symbol.h>
#include <Rcpp/Language.h>
#include <Rcpp/Pairlist.h>
#include <Rcpp/StretchyList.h>
#include <Rcpp/Function.h>
#include <Rcpp/WeakReference.h>
#include <Rcpp/Formula.h>
#include <Rcpp/DataFrame.h>
#include <Rcpp/Index.h>
#include <Rcpp/Array.h>
#include <Rcpp/Dots.h>
#include <Rcpp/NamedDots.h>

#include <Rcpp/Context.h>
#include <Rcpp/Condition.h>

#include <Rmath.h>
#include <Rcpp/sugar/undoRmath.h>

#include <Rcpp/hash/hash.h>
#include <Rcpp/sugar/sugar.h>
#include <Rcpp/stats/stats.h>

#include <Rcpp/Rmath.h>

#include <Rcpp/api/meat/meat.h>

#endif
