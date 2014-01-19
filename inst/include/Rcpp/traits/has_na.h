#ifndef Rcpp__traits__has_na__h
#define Rcpp__traits__has_na__h

namespace Rcpp{
namespace traits{

/**
 * Indentifies if a given SEXP type has the concept of missing values
 * 
 * This is false by default and specialized for all types that do 
 * have the concept
 */
template<int RTYPE> struct has_na : public std::false_type{} ;

/**
 * integer vectors support missing values
 */
template<> struct has_na<INTSXP> : public std::true_type{};

/**
 * numeric vectors support missing values
 */
template<> struct has_na<REALSXP> : public std::true_type{};

/**
 * complex vectors support missing values
 */
template<> struct has_na<CPLXSXP> : public std::true_type{};

/**
 * character vector support missing values
 */
template<> struct has_na<STRSXP> : public std::true_type{};

/**
 * logical vectors support missing values
 */
template<> struct has_na<LGLSXP> : public std::true_type{};

}
}

#endif
