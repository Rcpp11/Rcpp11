#ifndef Rcpp__vector__no_init_h
#define Rcpp__vector__no_init_h
  
namespace Rcpp{
    
class no_init {
public:
    no_init(int size_): size(size_){}
    inline int get() const { return size; }
    
    template <int RTYPE> 
    operator Vector<RTYPE>() { 
        return Rf_allocVector(RTYPE, size) ; 
    }
    
private:
    int size ;
} ;
  
}
#endif
