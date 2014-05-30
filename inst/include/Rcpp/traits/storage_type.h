#ifndef Rcpp__traits__storage_type__h
#define Rcpp__traits__storage_type__h

namespace Rcpp{
namespace traits{

/**
 * Indicates the storage type associated with a SEXP type
 * for example: storage_type<INTSXP>::type is a typedef to int
 *
 * The default is SEXP, which works for VECSXP, EXPRSXP and STRSXP
 */
template<int RTYPE> struct storage_type{ 
    typedef SEXP type ;
} ;

/**
 * Total specialization for integer vector (INTSXP)
 * typedef to int
 */
template<> struct storage_type<INTSXP>{ 
    typedef int type ;
} ;

/**
 * Total specialization for numeric vectors (REALSXP)
 * typedef to double
 */
template<> struct storage_type<REALSXP>{ 
    typedef double type ;
} ;

/**
 * Total specialization for numeric vectors (CPLXSXP)
 * typedef to Rcomplex
 */
template<> struct storage_type<CPLXSXP>{ 
    typedef Rcomplex type ;
} ;

/**
 * Total specialization for raw vectors (RAWSXP)
 * typedef to Rbyte
 */
template<> struct storage_type<RAWSXP>{ 
    typedef Rbyte type ;
} ;

/**
 * Total specialization for logical vectors (LGLSXP)
 * typedef to int
 */
template<> struct storage_type<LGLSXP>{ 
    typedef Rboolean type ;
} ;

} // traits
} // Rcpp

#endif
