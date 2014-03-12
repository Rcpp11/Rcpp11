#ifndef Rcpp__vector__instantiation_h
#define Rcpp__vector__instantiation_h

namespace Rcpp{
    
    typedef Vector<CPLXSXP> ComplexVector ;  
    typedef Vector<INTSXP> IntegerVector ;
    typedef Vector<LGLSXP> LogicalVector ;
    typedef Vector<REALSXP> NumericVector ;
    typedef Vector<REALSXP> DoubleVector ;
    typedef Vector<RAWSXP> RawVector ;
    
    typedef Vector<STRSXP> CharacterVector ;   
    typedef Vector<STRSXP> StringVector ;
    typedef Vector<VECSXP> GenericVector ;
    typedef Vector<VECSXP> List ;
    typedef Vector<EXPRSXP> ExpressionVector ;
    
}
#endif
