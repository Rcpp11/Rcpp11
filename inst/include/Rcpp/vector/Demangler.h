#ifndef Rcpp__vector__Demangler_h
#define Rcpp__vector__Demangler_h

namespace Rcpp{
    
    DEMANGLE_ECHO(Rcpp::DoubleVector) 
    DEMANGLE_ECHO(Rcpp::StringVector) 
    DEMANGLE_ECHO(Rcpp::IntegerVector) 
    DEMANGLE_ECHO(Rcpp::LogicalVector) 
    DEMANGLE_ECHO(Rcpp::ComplexVector) 
    DEMANGLE_ECHO(Rcpp::ExpressionVector) 
    DEMANGLE_ECHO(Rcpp::List) 
    DEMANGLE_ECHO(Rcpp::RawVector)
    
    DEMANGLE_ECHO(Rcpp::DoubleMatrix) 
    DEMANGLE_ECHO(Rcpp::StringMatrix) 
    DEMANGLE_ECHO(Rcpp::IntegerMatrix) 
    DEMANGLE_ECHO(Rcpp::LogicalMatrix) 
    DEMANGLE_ECHO(Rcpp::ComplexMatrix) 
    DEMANGLE_ECHO(Rcpp::ExpressionMatrix) 
    DEMANGLE_ECHO(Rcpp::GenericMatrix) 
    DEMANGLE_ECHO(Rcpp::RawMatrix)
    
}
#endif
