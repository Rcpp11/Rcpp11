#ifndef Rcpp11_h
#define Rcpp11_h

// #define RCPP11_EXPERIMENTAL_PRESERVE
#define RCPP11_EXPERIMENTAL_PARALLEL

#include <Rcpp/platform.h>

#include <cmath>
#include <csetjmp>

#include <initializer_list>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <map>

#include <Rcpp/macros/macros.h>
#include <Rcpp/internal/library.h>
#include <Rcpp/R.h>

#include <Rcpp/routines.h>
#include <Rcpp/wrap/forward.h>

#include <Rcpp/protection/protection.h>

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

#include <set>
#include <stdexcept>
#include <vector>
#include <deque>
#include <functional>
#include <numeric>
#include <algorithm>
#include <complex>
#include <climits>
#include <typeinfo>
#include <tuple>
#include <utility>
#include <future>
#include <chrono>

#include <Rcpp/api/CRTP.h>
#include <Rcpp/complex.h>
#include <Rcpp/utils/tinyformat.h>

#include <Rcpp/exceptions.h>
#include <Rcpp/internal/interrupt.h>
#include <Rcpp/Demangler.h>
#include <Rcpp/utils/describe.h>

#if defined(RCPP11_EXPERIMENTAL_PARALLEL)
#include <thread>
#endif

#include <Rcpp/utils/parallel/parallel.h>

namespace Rcpp{
    
    inline bool is_null(SEXP x){ 
        return Rf_isNull(x) ;   
    }
    inline bool is_object(SEXP x){ 
        return Rf_isObject(x) ;   
    }
    inline bool inherits(SEXP x, const char* klass){ 
        return Rf_inherits(x, klass) ;   
    }
    
    inline std::string short_file_name(const char* file) {
        std::string f(file) ;
        size_t pos = f.find_last_of("/") ;
        if( pos == std::string::npos ) return f ;
        return f.substr( pos + 1 ) ;
    }

    inline bool derives_from( SEXP cl, const std::string& clazz ){
        if(cl == R_NilValue) return false ;

        // simple test for exact match
        if( ! clazz.compare( CHAR(STRING_ELT(cl, 0)) ) ) return true ;

        SEXP containsSym = Rf_install("contains");
        Shield<SEXP> contains = R_do_slot(R_getClassDef(CHAR(Rf_asChar(cl))),containsSym);
        SEXP res = Rf_getAttrib(contains,R_NamesSymbol );
        if(res == R_NilValue) return false ;

        return std::any_of(
            VECTOR_PTR(res), VECTOR_PTR(res) + LENGTH(res),
            [&](SEXP s){ return clazz == CHAR(s) ; }
        ) ;
    }

    class String ;
    class PreserveStorage ;
    class NoProtectStorage ;

    template <int RTYPE, typename Storage = PreserveStorage> class Vector ;
    template <int RTYPE, typename Storage = PreserveStorage> class Matrix ;

    typedef Vector<STRSXP> CharacterVector ;
    typedef Vector<VECSXP> List ;
    typedef Vector<EXPRSXP> ExpressionVector ;

    template <typename Storage> class RObject_Impl ;
    template <typename Storage> class Language_Impl ;
    template <typename Storage> class Pairlist_Impl ;
    template <typename Storage> class Environment_Impl ;
    template <typename Storage> class Promise_Impl ;
    template <typename Storage> class WeakReference_Impl ;
    template <typename Storage> class S4_Impl ;
    template <typename Storage> class Formula_Impl ;
    template <typename Storage> class Reference_Impl ;
    template <typename Storage> class Function_Impl ;
    template <typename Storage> class DataFrame_Impl ;
    template <typename Storage> class Symbol_Impl ;

    typedef RObject_Impl<PreserveStorage> RObject ;
    typedef Language_Impl<PreserveStorage> Language ;
    typedef Pairlist_Impl<PreserveStorage> Pairlist ;
    typedef Environment_Impl<PreserveStorage> Environment ;
    typedef Promise_Impl<PreserveStorage> Promise ;
    typedef WeakReference_Impl<PreserveStorage> WeakReference ;
    typedef S4_Impl<PreserveStorage> S4 ;
    typedef Formula_Impl<PreserveStorage> Formula ;
    typedef Reference_Impl<PreserveStorage> Reference ;
    typedef Function_Impl<PreserveStorage> Function ;
    typedef DataFrame_Impl<PreserveStorage> DataFrame ;
    typedef Symbol_Impl<NoProtectStorage> Symbol ;
    
}
namespace Rcpp{
    class Na_Proxy ;
    
    template <typename T> T as( SEXP ) ;
}

#include <Rcpp/internal/na.h>
#include <Rcpp/traits/traits.h>
#include <Rcpp/sugar/functional/functional.h>
#include <Rcpp/Named.h>

#include <Rcpp/internal/caster.h>
#include <Rcpp/internal/r_vector.h>
#include <Rcpp/r_cast.h>

#include <Rcpp/internal/r_coerce.h>
#include <Rcpp/as/forward.h>
#include <Rcpp/InputParameter.h>
#include <Rcpp/is.h>

#include <Rcpp/wrap/wrap.h>

#include <Rcpp/internal/Proxy_Iterator.h>

#include <Rcpp/longlong.h>
#include <Rcpp/transient_vector.h>

#include <Rcpp/registration/registration.h>

#include <Rcpp/storage/storage.h>
#include <Rcpp/proxy/GenericProxy.h>
#include <Rcpp/proxy/proxy.h>
#include <Rcpp/Symbol.h>

#include <Rcpp/storage/PreserveStorage.h>
#include <Rcpp/storage/NoProtectStorage.h>

#include <Rcpp/Node.h>
#include <Rcpp/grow.h>
#include <Rcpp/DottedPairImpl.h>

#include <Rcpp/structure.h>

#include <Rcpp/RObject.h>

#include <Rcpp/Promise.h>
#include <Rcpp/S4.h>
#include <Rcpp/Reference.h>
#include <Rcpp/clone.h>
#include <Rcpp/Environment.h>
#include <Rcpp/Evaluator.h>

#include <Rcpp/Vector.h>
#include <Rcpp/ListOf.h>

#include <Rcpp/sugar/nona/nona.h>

#include <Rcpp/XPtr.h>
#include <Rcpp/Function.h>
#include <Rcpp/Language.h>
#include <Rcpp/Pairlist.h>
#include <Rcpp/StretchyList.h>
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

#include <Rcpp/sugar/sugar.h>
#include <Rcpp/stats/stats.h>

#include <Rcpp/Rmath.h>

#include <Rcpp/api/meat/meat.h>

#include <Rcpp/Timer.h>

namespace Rcpp11 = Rcpp ;

#endif
