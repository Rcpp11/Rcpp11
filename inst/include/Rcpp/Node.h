#ifndef Rcpp_Node_h
#define Rcpp_Node_h

namespace Rcpp{
      
    class Node : public NodeProxyPolicy<Node> {
    public:
        Node( SEXP data_ ) : data(data_){}    
    
        Node next() const {
            return CDR(data) ;
        }
        
        bool last() const {
            return CDR(data) == R_NilValue ;  
        }
        
        inline SEXP get() const { 
            return data; 
        }
        
    private:
        SEXP data ; 
        
    } ;
  
}

#endif
