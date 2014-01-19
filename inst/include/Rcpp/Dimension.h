#ifndef Rcpp_Dimension_h
#define Rcpp_Dimension_h

#define R_NO_REMAP
#include <Rinternals.h>
#include <vector>
 
namespace Rcpp{ 

    class Dimension {
    public:
	    typedef std::vector<int>::reference reference ;
	    typedef std::vector<int>::const_reference const_reference ;
	    
	    Dimension(SEXP dims) ;
	    inline Dimension(const size_t& n1) : dims(1){
            dims[0] = n1 ;
        }
	    inline Dimension(const size_t& n1, const size_t& n2) : dims(2){
            dims[0] = n1 ;
            dims[1] = n2 ;
        }
	    inline Dimension(const size_t& n1, const size_t& n2, const size_t& n3) : dims(3){
            dims[0] = n1 ;
            dims[1] = n2 ;
            dims[2] = n3 ;
        }
	    operator SEXP() const ;
	    
	    inline int size() const {
	        return static_cast<int>( dims.size() ) ;
	    }
	    inline int prod() const {
	        return std::accumulate( dims.begin(), dims.end(), 1, std::multiplies<int>() ) ;    
	    }
	    
	    inline reference operator[](int i){
	        return dims.at(i) ;
	    }
	    inline const_reference operator[](int i) const{
	        return dims.at(i) ;    
	    }
	    
    private:
        std::vector<int> dims;
    };

}
#endif
