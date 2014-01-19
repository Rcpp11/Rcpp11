#ifndef Rcpp_api_meat_Dimension_h
#define Rcpp_api_meat_Dimension_h

namespace Rcpp{

    // Dimension
    inline Dimension::Dimension(SEXP x): dims(){
        dims = as< std::vector<int> >(x) ;
    }
        
    inline Dimension::operator SEXP() const {
        return wrap( dims.begin(), dims.end() ) ;
    }
    
}
#endif
