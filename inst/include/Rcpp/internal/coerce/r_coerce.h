#ifndef RCPP_INTERNAL_COERCE_RCOERCE_H
#define RCPP_INTERNAL_COERCE_RCOERCE_H

namespace Rcpp{
    namespace internal{
            
        template <> inline int r_coerce<INTSXP,INTSXP>(int from) { return from ; }
        template <> inline Rboolean r_coerce<LGLSXP,LGLSXP>(Rboolean from) { return from ; }
        template <> inline double r_coerce<REALSXP,REALSXP>(double from) { return from ; }
        template <> inline Rcomplex r_coerce<CPLXSXP,CPLXSXP>(Rcomplex from) { return from ; }
        template <> inline Rbyte r_coerce<RAWSXP,RAWSXP>(Rbyte from) { return from ; }
        
        // -> INTSXP
        template <> inline int r_coerce<LGLSXP,INTSXP>(Rboolean from){
            return (from==NA_VALUE) ? NA_INTEGER : from ;
        }
        template <> inline int r_coerce<REALSXP,INTSXP>(double from){
            if (Rcpp::internal::is_NaN(from)) return NA_INTEGER;
            else if (from > INT_MAX || from <= INT_MIN ) {
                return NA_INTEGER;
            }
            return static_cast<int>(from);
        
        }
        template <> inline int r_coerce<CPLXSXP,INTSXP>(Rcomplex from){
            return r_coerce<REALSXP,INTSXP>(from.r) ;
        }
        template <> inline int r_coerce<RAWSXP,INTSXP>(Rbyte from){
            return static_cast<int>(from);
        }
        
        // -> REALSXP
        template <> inline double r_coerce<LGLSXP,REALSXP>(Rboolean from){
            return from == NA_VALUE ? NA_REAL : static_cast<double>(from) ;
        }
        template <> inline double r_coerce<INTSXP,REALSXP>(int from){
            return from == NA_INTEGER ? NA_REAL : static_cast<double>(from) ; 
        }
        template <> inline double r_coerce<CPLXSXP,REALSXP>(Rcomplex from){
            return from.r ;
        }
        template <> inline double r_coerce<RAWSXP,REALSXP>(Rbyte from){
            return static_cast<double>(from) ;
        }
        
        // -> LGLSXP
        template <> inline Rboolean r_coerce<REALSXP,LGLSXP>(double from){
            return ( from == NA_REAL ) ? NA_VALUE : ( from==0.0 ? FALSE : TRUE ) ;
        }
        template <> inline Rboolean r_coerce<INTSXP,LGLSXP>(int from){
            return ( from == NA_INTEGER ) ? NA_VALUE : ( from == 0 ? FALSE : TRUE );
        }
        template <> inline Rboolean r_coerce<CPLXSXP,LGLSXP>(Rcomplex from){
            if( from.r == NA_REAL ) return NA_VALUE ;
            if( from.r == 0.0 || from.i == 0.0 ) return FALSE ;
            return TRUE ;
        }
        template <> inline Rboolean r_coerce<RAWSXP,LGLSXP>(Rbyte from){
            if( from != static_cast<Rbyte>(0) ) return TRUE ;
            return FALSE ;
        }
        
        // -> RAWSXP
        template <> inline Rbyte r_coerce<REALSXP,RAWSXP>(double from){
            if( from == NA_REAL) return static_cast<Rbyte>(0) ; 
            return r_coerce<INTSXP,RAWSXP>(static_cast<int>(from)) ;
        }
        template <> inline Rbyte r_coerce<INTSXP,RAWSXP>(int from){
            return (from < 0 || from > 255) ? static_cast<Rbyte>(0) : static_cast<Rbyte>(from) ;
        }
        template <> inline Rbyte r_coerce<CPLXSXP,RAWSXP>(Rcomplex from){
            return r_coerce<REALSXP,RAWSXP>(from.r) ;
        }
        template <> inline Rbyte r_coerce<LGLSXP,RAWSXP>(Rboolean from){
            return static_cast<Rbyte>(from == TRUE) ;
        }
        
        // -> CPLXSXP
        template <> inline Rcomplex r_coerce<REALSXP,CPLXSXP>(double from){
            if( from == NA_REAL ){
                return Rcomplex{ NA_REAL, NA_REAL };
            } else{
                return Rcomplex{ from, 0.0 };
            }
        }
        template <> inline Rcomplex r_coerce<INTSXP,CPLXSXP>(int from){
            if( from == NA_INTEGER ){
                return Rcomplex{ NA_REAL, NA_REAL };
            } else{
                return Rcomplex{ static_cast<double>(from), 0.0 };
            }
        }
        template <> inline Rcomplex r_coerce<RAWSXP,CPLXSXP>(Rbyte from){
            return Rcomplex { static_cast<double>(from), 0.0 };
        }
        template <> inline Rcomplex r_coerce<LGLSXP,CPLXSXP>(Rboolean from){
            switch(from){
                case TRUE: return Rcomplex{ 1.0, 0.0 } ;
                case FALSE: return Rcomplex {0.0, 0.0 } ;
                default: break;
            }
            return Rcomplex{ NA_REAL, NA_REAL } ;
        }
    
    }
}

#endif
