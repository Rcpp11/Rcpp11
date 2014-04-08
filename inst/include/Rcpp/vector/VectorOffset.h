#ifndef Rcpp__vector__VectorOffset_h
#define Rcpp__vector__VectorOffset_h

namespace Rcpp{

    template <typename Vector>
    class VectorOffset {
    private:
        Vector& get_ref() { return static_cast<Vector&>(*this) ; }
        const Vector& get_ref() const { return static_cast<const Vector&>(*this) ; }
        
        
    public:
        
        inline R_len_t length() const { return ::Rf_length( get_ref() ) ; }
        inline R_len_t size() const { return length() ; }
    
        R_len_t offset(const std::string& name) const {
            SEXP names = RCPP_GET_NAMES( get_ref() ) ;
            if( names == R_NilValue ) throw index_out_of_bounds();
            int n = size() ;
    
            SEXP* data = internal::r_vector_start<STRSXP>(names) ;
            int index = std::find( data, data+n, Rf_mkChar(name.c_str()) ) - data ;
            if( index == n ) throw index_out_of_bounds() ;
            return index ;
        }
    
    } ;
        
}

#endif
