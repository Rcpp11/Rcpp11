#ifndef Rcpp__sugar_lazy_c_h
#define Rcpp__sugar_lazy_c_h

namespace Rcpp {

    namespace internal {
    
        template <typename Current>
        int max_type(Current x) {
            return TYPEOF(x);
        }
        
        template <typename Current, typename... Rest>
        int max_type(Current lhs, Rest... rest) {
            return std::max( max_type(lhs), max_type(rest...) );
        }
    
    }

    #define FUSE_CASE(RTYPE) wrap( fuse( as<Vector<RTYPE>>(args)... ) ); 

    template <typename... Args>
    SEXP c(Args... args) {
        static_assert( traits::all_convertible<SEXP,Args...>::type::value, "c(...) requires that all types are convertible to SEXP" ) ;  
        int maxtype = internal::max_type(args...);
        switch (maxtype) {
            case INTSXP : return FUSE_CASE(INTSXP );
            case REALSXP: return FUSE_CASE(REALSXP);
            case STRSXP : return FUSE_CASE(STRSXP );
            case LGLSXP : return FUSE_CASE(LGLSXP );
            case VECSXP : return FUSE_CASE(VECSXP );
            default: {
                    stop("Unhandled RTYPE %s encountered", Rf_type2char(maxtype));
            }
        }
        return R_NilValue ;
    }  
    
    #undef FUSE_CASE

}

#endif
