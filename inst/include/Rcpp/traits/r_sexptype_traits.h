#ifndef Rcpp__traits__r_sexptype_traits__h
#define Rcpp__traits__r_sexptype_traits__h

namespace Rcpp{
namespace traits{

/**
 * template that returns the SEXP type that is appropriate for 
 * the type T, this is allways VECSXP (lists) unless it is specialized
 */
template <typename T> struct r_sexptype_traits{ enum{ rtype = VECSXP }; } ;
template<> struct r_sexptype_traits<int>{ enum{ rtype = INTSXP } ; } ;
template<> struct r_sexptype_traits<const int>{ enum{ rtype = INTSXP } ; } ;
template<> struct r_sexptype_traits<double>{ enum{ rtype = REALSXP } ; } ;
template<> struct r_sexptype_traits<const double>{ enum{ rtype = REALSXP } ; } ;
template<> struct r_sexptype_traits<bool>{ enum{ rtype = LGLSXP } ; } ;
template<> struct r_sexptype_traits<Rboolean>{ enum{ rtype = LGLSXP } ; } ;
template<> struct r_sexptype_traits<std::string>{ enum{ rtype = STRSXP } ; } ;
template<> struct r_sexptype_traits<Rcomplex>{ enum{ rtype = CPLXSXP } ; } ;
template<> struct r_sexptype_traits<Rbyte>{ enum{ rtype = RAWSXP } ; } ;


template<> struct r_sexptype_traits<unsigned int>{ enum{ rtype = REALSXP } ; } ;
template<> struct r_sexptype_traits<float>{ enum{ rtype = REALSXP } ; } ;

/* long are represented as numeric vectors which allows more precision 
   to be preserved than int */
template<> struct r_sexptype_traits<long>{ enum{ rtype = REALSXP } ; } ;
template<> struct r_sexptype_traits<unsigned long>{ enum{ rtype = REALSXP } ; } ;

/* long double are represented as numeric vectors because we cannot do better in R
   some precision will be lost though
*/
template<> struct r_sexptype_traits<long double>{ enum{ rtype = REALSXP } ; } ;

/* short are represented as integer vector in R
*/
template<> struct r_sexptype_traits<short>{ enum{ rtype = INTSXP } ; } ;
template<> struct r_sexptype_traits<unsigned short>{ enum{ rtype = INTSXP } ; } ;

/* std::complex */
template<> struct r_sexptype_traits< std::complex<double> >{ enum{ rtype = CPLXSXP } ; } ;
template<> struct r_sexptype_traits< std::complex<float> >{ enum{ rtype = CPLXSXP } ; } ;

/**
 * Indicates if a primitive type needs a static_cast
 */
template <typename T> struct r_sexptype_needscast    : public std::true_type{}; 
template<> struct r_sexptype_needscast<int>          : public std::false_type{} ;
template<> struct r_sexptype_needscast<double>       : public std::false_type{} ;
template<> struct r_sexptype_needscast<Rcomplex>     : public std::false_type{} ;
template<> struct r_sexptype_needscast<Rbyte>        : public std::false_type{} ;


} // traits
} // Rcpp

#endif
